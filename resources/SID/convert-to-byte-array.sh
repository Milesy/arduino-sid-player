#echo "Converting SID dump [%1] to byte array."
xxd -i $1 > $1_byte-array.txt
