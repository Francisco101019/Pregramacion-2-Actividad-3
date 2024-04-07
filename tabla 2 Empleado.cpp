#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>

using namespace std;

int main()
{

    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;




    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    ret = SQLConnect(hDbc, (SQLWCHAR*)L"UNI", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {

        cout << "connected to database succesfully" << endl;

        SQLHSTMT hStmt;
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);



        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Empleado", SQL_NTS);

        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            SQLCHAR No_de_Empleado[10];

            SQLCHAR Nombre[30];
            SQLCHAR Apellido_Paterno[30];
            SQLCHAR Apellido_Materno[30];
            //SQLCHAR Fecha_de_Nacimiento[30];
            SQLCHAR RFC[20];
            SQLCHAR Puesto[15];
            SQLCHAR No_de_Centro[10];



            cout << "+-------------------------------------------------------------------------+" << endl;
            cout << "|                                 Empleado:                               |" << endl;
            cout << "+-------------------------------------------------------------------------+" << endl;
            cout << "|                                                                         |" << endl;
            cout << "|                                                                         |" << endl;

            while (SQLFetch(hStmt) == SQL_SUCCESS)
            {
                SQLGetData(hStmt, 1, SQL_C_CHAR, No_de_Empleado, sizeof(No_de_Empleado), NULL);
                SQLGetData(hStmt, 2, SQL_C_CHAR, Nombre, sizeof(Nombre), NULL);
                SQLGetData(hStmt, 3, SQL_C_CHAR, Apellido_Paterno, sizeof(Apellido_Paterno), NULL);
                SQLGetData(hStmt, 4, SQL_C_CHAR, Apellido_Materno, sizeof(Apellido_Materno), NULL);
                //SQLGetData(hStmt, 5, SQL_C_CHAR, Fecha_de_Nacimiento, sizeof(Fecha_de_Nacimiento), NULL);
                SQLGetData(hStmt, 6, SQL_C_CHAR, RFC, sizeof(RFC), NULL);
                SQLGetData(hStmt, 7, SQL_C_CHAR, Puesto, sizeof(Puesto), NULL);
                SQLGetData(hStmt, 8, SQL_C_CHAR, No_de_Centro, sizeof(No_de_Centro), NULL);


                cout << "| " << No_de_Empleado << "  " << Nombre << "  " << Apellido_Paterno<<"  " << Apellido_Materno<< "  " << RFC<<"  " << Puesto<< "  " << No_de_Centro << "|" << endl;

            }
            cout << "|                                                                        |" << endl;
            cout << "|                                                                        |" << endl;
            cout << "+------------------------------------------------------------------------+" << endl;

        }

        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    }

        else {
            cout << "failed to connected to database." << endl;

        }

        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

        return 0;

    }




