import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    total = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    cash = total[0]["cash"]

    rows = db.execute("SELECT symbol, SUM(shares) as total_shares FROM inventory WHERE user_id = :user_id GROUP BY symbol",user_id=session["user_id"])
    index = []
    grandtotal = 0
    for row in rows:
        stock = lookup(row["symbol"])
        index.append({"symbol" :stock["symbol"], "name" :stock["name"], "shares" :row["total_shares"], "price" :usd(stock["price"]), "total" :usd(stock["price"] * row["total_shares"])})

        grandtotal += stock["price"] * row["total_shares"]

    grandtotal += cash
    return render_template("index.html", rows=rows, index=index, cash=usd(cash), grandtotal = usd(grandtotal))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)
        if not stock:
            return apology("Invalid symbol")

        shares = int(request.form.get("shares"))

        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

        current_cash = rows[0]["cash"]
        cost = stock["price"] * float(shares)

        if cost > current_cash:
            return apology("not enough funds")

        else:
            db.execute("UPDATE users SET cash = cash - :cost WHERE id = :user_id", cost=cost, user_id=session["user_id"])
            db.execute("INSERT INTO inventory (user_id, symbol, name, shares, price) VALUES(:user_id, :symbol, :name, :shares, :price)",
                user_id=session["user_id"], symbol=symbol, name=stock["name"], shares=shares, price=stock["price"])
            flash("Bought!")
            return redirect("/")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    table = db.execute("SELECT * FROM inventory WHERE user_id = :user_id", user_id=session["user_id"])

    return render_template("history.html", table=table)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)
        if stock == None:
            return apology("Invalid Symbol", 400)
        else:
            return render_template("quoted.html", stock = stock)



@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")

        if not username:
            return apology("You must provide a name")

        password = request.form.get("password")
        password2 = request.form.get("password2")

        if password != password2:
            return apology("Passwords do not match")
        elif not password or not password2:
            return apology("You must provide a password")

        if db.execute("SELECT * FROM users WHERE username = :username", username=username):
            return apology("Username is already in use.", 403)

        row = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=username, hash=generate_password_hash(password))
        session["user_id"] = row
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        rows = db.execute("SELECT symbol FROM inventory WHERE user_id = :user_id GROUP BY symbol",user_id=session["user_id"])
        index = []
        for row in rows:
            stock = lookup(row["symbol"])
            index.append(stock)
        return render_template("sell.html", index=index)

    else:
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)
        if not stock:
            return apology("Invalid symbol")

        shares = int(request.form.get("shares"))

        rows = db.execute("SELECT SUM(shares) as total_shares FROM inventory WHERE user_id = :user_id", user_id=session["user_id"])

        current_shares = rows[0]["total_shares"]
        selling = stock["price"] * float(shares)

        if int(shares) > current_shares:
            return apology("Too many shares")

        db.execute("UPDATE users SET cash = cash + :selling WHERE id = :user_id", selling=selling, user_id=session["user_id"])
        db.execute("INSERT INTO inventory (user_id, symbol, name, shares, price) VALUES(:user_id, :symbol, :name, :shares, :price)",
            user_id=session["user_id"], symbol=symbol, name=stock["name"], shares=-shares, price=stock["price"])
        flash("Sold!")
        return redirect("/")

@app.route("/funds", methods=["GET", "POST"])
@login_required
def funds():
    if request.method == "GET":
        return render_template("funds.html")
    else:
        funds = int(request.form.get("funds"))
        db.execute("UPDATE users SET cash = cash + :funds WHERE id = :user_id", funds=funds, user_id=session["user_id"])
        return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
