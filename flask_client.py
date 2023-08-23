import json
import socket
from forms import Test
from flask_client_header import disconnect_from_server, send_data_to_server
from flask import Flask, render_template, request, flash, redirect, url_for, session

HEADER = 64
PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
DISCONNECT_MESSAGE = "!!!DISCONNECT"
FORMAT = 'utf-8'


app = Flask(__name__)

app.config['SECRET_KEY'] = '0b8da1363835a1f14def74db4df9668e'


@app.route("/")
@app.route("/home")
def home():

    return render_template('home.html')


@app.route("/apply_for_loan", methods=['GET', 'POST'])
def apply_for_loan():
    menu_response = 1
    form = Test()

    while form.validate_on_submit():
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect(ADDR)
        
        user_name = form.username.data
        user_credit_score = form.user_credit_score.data
        user_monthly_income = form.user_monthly_income.data
        user_financial_reserves = form.user_financial_reserves.data
        user_debt_to_income_ratio = form.user_debt_to_income_ratio.data
        user_loan_amoumnt_requested = form.user_loan_amoumnt_requested.data
        user_loan_duration = form.user_loan_duration.data
        
        customer_data = {
            "user_name" : user_name,
            "user_credit_score" : user_credit_score,
            "user_monthly_income" : user_monthly_income,
            "user_financial_reserves" : user_financial_reserves,
            "user_debt_to_income_ratio" : user_debt_to_income_ratio,
            "user_loan_amoumnt_requested" : user_loan_amoumnt_requested,
            "user_loan_duration" : user_loan_duration,
            "user_loan_id" : None,
            "user_has_loan_id" : None
        }
        
        instructions = {
            "menu_response" : menu_response,
            "dev_menu_response" : None,
            "search_menu_response" : None,
            "generate_data_for_db" : False,
            "num_data_to_generate" : None,
            "perform_data_analysis_on_all_generated_csv_data" : False,
            "store_all_db_data_for_external_analysis" : False
        }
        
        data_to_send = {
            "customer_data" : customer_data,
            "instructions" : instructions
        }
        
        json_data = json.dumps(data_to_send, indent = 2)
        print(json_data)
        
        operation_state, retrieved_user_data = send_data_to_server(json_data, client)
        
        disconnect_from_server(client)
        # del retrieved_user_data, temp_operation_state, temp_retrieved_data
        
        if  (operation_state["added_user_data_successfully"] == True):
            session['customer_data'] = customer_data
            return redirect(url_for("display_loan_data"))

        
        
    return render_template('apply_for_loan.html', form = form, title = 'apply_for_loan')


@app.route("/display_loan_data", methods = ['GET', 'POST'])
def display_loan_data():
    customer_data = session.get('customer_data')
    
    return render_template('display_loan_data.html', customer_data = customer_data, title = 'display_loan_data')
    
    


if __name__ == '__main__':
    app.run(debug = True)