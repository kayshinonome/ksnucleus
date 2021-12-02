.section .text
.global detect_v86
.type detect_v86, @function

.code16
detect_v86:
   smsw    %ax
   and     %eax,1
   ret
