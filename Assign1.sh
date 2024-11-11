
ans='y'

until [ "$ans" = 'n' ]
do
    echo "1: Create Database"
    echo "2: View Database"
    echo "3: Insert Record"
    echo "4: Search Record"
    echo "5: Modify Record"
    echo "6: Delete Record"
    echo "Enter Choice"
    read ch

    case "$ch" in
        1)
            echo "Enter Filename"
            read fname
            echo "Enter Database Name"
            read db
            echo "Enter Field 1"
            read f1
            echo "Enter Field 2"
            read f2
            printf "\t%s$db>>$fname" 
		printf "%s\t%s\n" "$f1" "$f2" >> "$fname"
            echo "Record Created"
            ;;

        2)
            echo "Enter Filename"
            read fname
            if [ -e "$fname" ]; then
                cat "$fname"
            else
                echo "File does not exist"
            fi
            ;;

        3)
            echo "Enter Filename"
            read fname
            echo "How Many Entries Do you want to insert?"
            read n
            while [ "$n" -gt 0 ]
            do
                echo "Enter Field 1 Value"
                read f1
                echo "Enter Field 2 Value"
                read f2
                printf "\n%s\t%s\n" "$f1" "$f2" >> "$fname"
                n=$((n - 1))
            done
            echo "Record Inserted"
            ;;

        4)
            echo "Enter Filename"
            read fname
            if [ -e "$fname" ]; then
                echo "Enter Field 1 Value to Search"
                read f1
                grep "$f1" "$fname"
                if [ $? -eq 0 ]; then
                    echo "Record found"
                else
                    echo "Record not found"
                fi
            else
                echo "File does not exist"
            fi
            ;;

        5)
            echo "Enter Filename"
            read fname
            if [ -e "$fname" ]; then
                echo "Enter Field 1 Value to Modify"
                read f1
                grep "$f1" "$fname"
                if [ $? -eq 0 ]; then
                    echo "Record found"
                    grep -v "$f1" "$fname" > temp.data
                    echo "Enter new Field 1 value"
                    read newf1
                    echo "Enter new Field 2 value"
                    read newf2
                    printf "%s\t%s\n" "$newf1" "$newf2" >> temp.data
                    mv temp.data "$fname"
                    echo "Record modified"
                else
                    echo "Record not found"
                fi
            else
                echo "File does not exist"
            fi
            ;;

        6)
            echo "Enter Filename"
            read fname
            if [ -e "$fname" ]; then
                echo "Enter Field 1 Value to Delete"
                read f1
                grep "$f1" "$fname"
                if [ $? -eq 0 ]; then
                    echo "Record found"
                    grep -v "$f1" "$fname" > temp.data
                    mv temp.data "$fname"
                    echo "Record Deleted"
                else
                    echo "Record not found"
                fi
            else
                echo "File does not exist"
            fi
            ;;

        *)
            echo "Invalid choice"
            ;;
    esac

    echo "Do you want to continue? (y/n)"
    read ans
done

