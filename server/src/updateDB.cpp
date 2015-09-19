// #include "updateDB.h"
// #include <sstream>
// #include <string>
// #include "stdio.h"
//
// unsigned char clientUpdateDB(const Client &client)
// {
//   MYSQL mysql;
//   string query;
//   MYSQL_RES *result;
//   mysql_init(&mysql);
//
//   if (!mysql_real_connect(&mysql,"localhost", "root" , "913256" , "game" , 0 , NULL , 0))
//   {//判断连接是否失败。
//     printf("Failed to connect to database: Error: %s/n",  mysql_error(&mysql));
//     return -1;
//   }
//
//   std::string score;
//   stringstream converter;
//   converter<<client.score;
//   converter>>score;
//
//   query="update user set score=" + score + " where username='" + client.userName + "'";
//
//   do
//   {
//     result = mysql_store_result( &mysql );
//     mysql_free_result(result);
//   }while( !mysql_next_result( &mysql ) );
//
//   if(mysql_real_query(&mysql, query.c_str(),query.length()))
//   {
//     printf("Failed to exec query : Error:%s",mysql_error(&mysql));
//     return 1;   //没有此用户
//   }
//
//   do
//   {
//     result = mysql_store_result( &mysql );
//     mysql_free_result(result);
//   }while( !mysql_next_result( &mysql ) );
//
//   return 0;
// }
//
// unsigned char getClientInfoDB(Client &client)
// {
//   MYSQL mysql;
//   string query;
//   MYSQL_RES *result;
//   mysql_init(&mysql);
//
//   if (!mysql_real_connect(&mysql,"localhost", "root" , "913256" , "game" , 0 , NULL , 0))
//   {//判断连接是否失败。
//     printf("Failed to connect to database: Error: %s/n",  mysql_error(&mysql));
//     return -1;
//   }
//
//   query="select * from user where username='" + client.userName + "'";
//
//   //清空结果集
//   do
//   {
//     result = mysql_store_result( &mysql );
//     mysql_free_result(result);
//   }while( !mysql_next_result( &mysql ) );
//
//   if(mysql_real_query(&mysql, query.c_str(),query.length()))
//   {
//     printf("Failed to exec query : Error:%s",mysql_error(&mysql));
//     return 1;   //没有此用户
//   }
//
//   result=mysql_store_result(&mysql);
//
//   // printf("rows = %d",mysql_num_rows(result));
//
//   if(mysql_num_rows(result)!=1)
//   {
//       mysql_free_result(result);
//       return 2;   //多个同名用户
//   }
//
//   MYSQL_ROW row = mysql_fetch_row(result);
// //	printf("fetch row ok\r\n");
//   unsigned long *lengths=mysql_fetch_lengths(result);
//
//   stringstream converter;
//   converter<<std::string(row[3],lengths[3]);;
//   converter>>client.score;
// //	cout<<code<<"|"<<passwd<<"|"<<endl;
// 	mysql_free_result(result);
//   return 0; //登录成功
// }
