最近对网页是如何从服务端传输到客户端这一过程比较感兴趣，所以用现代c++写一个http服务器。  
参考[http protocol](https://www.ietf.org/rfc/rfc2616.txt)  

计划： 

- [ ] 实现一个可以回复GET请求的简易服务器，版本0.1



注意：  


HTTP/1.1 requests containing a message-body MUST include a valid Content-Length header field unless the server is known to be HTTP/1.1 compliant. If a request contains a message-body and a Content-Length is not given, the server SHOULD respond with 400 (bad request) if it cannot determine the length of the message, or with 411 (length required) if it wishes to insist on receiving a valid Content-Length.



here
