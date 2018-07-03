# movntps instruction has to operate on operands aligned on 16 bytes boundaries otherwise general protection error is raised by the CPU

python -c "print '8\n24\n56\n120\n248\n504\n1016\n2040\n4088\n8184'" | nc pwnable.kr 9022

#thanks for helping my experiment!
#flag : 1_w4nn4_br34K_th3_m3m0ry_4lignm3nt
