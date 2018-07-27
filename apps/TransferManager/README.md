# Transfer Manager

Transfer Manager is an application, which is using curl Library(https://github.com/curl/curl)
for transfering data with URL. Supporting HTTP, FTP download and upload.

## Example Usecase

-Create HTTP, FTP download/upload transfer request
-Run HTTP, FTP download/upload transfer 
-Abort HTTP, FTP download/upload transfer 
-Get info about transfer

## Create Request 

For create transfer request, is needed to create iTransferRequest and call method addTransfer() from manager

iTransferRequest contains: 
  - URL /std::string/ - web address, which is a reference to a web resource that specifies its location on a computer network 
  - Path /std::string/ - specifies a location in file system for a file 
  - Type /TransferType/ - represent type of transfer | HTTPUpload | HTTPDownload | FTPUpload | FTPDownload |

        flexd::rsm::conn::iTransferRequest request("http://test.url/test.dat" , ".../TransferManager/text2.txt", flexd::rsm::conn::HTTPDownload);
        mng.addTransfer(request);


## Run transfer

For run transfer, is needed call method runTransfer() at manager

        mng.runTransfer();
        
## Abort transfer

For abort transfer, is needed call method abortTransfer() at manager

        mng.abortTransfer();
        
## Get transfer info

For get transfer info, is needed call method getTransferInfo() at manager

        mng.getTransferInfo();
