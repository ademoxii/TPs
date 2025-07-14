STACK SEGMENT
     dw 64 DUP(0)
STACK ENDS
DATA SEGMENT   
menu db 13,10, 'PRACTICAL HOMEWORK -SYST2-', 13,10 
     db '- BENSALEM ADEM G10 -' ,13,10,
     db '----- THE MENU -----' ,13,10,
     db '1. ADD CONTACT', 13,10
     db '2. VIEW CONTACTS', 13,10
     db '3. SEARCH CONTACT', 13,10
     db '4. MODIFY CONTACT', 13,10
     db '5. DELETE CONTACT', 13,10
     db '6. EXIT', 13,10, 'YOUR CHOICE :$' 
    searchBuffer db 11 dup(0)   
    searchName db 13,10,'ENTER THE NAME :$'
    searchNumber db 13,10,'THE NUMBER IS :$'
    choice db ?                         
    msgINVALID db 13,10, 'INVALID CHOICE', 13,10, '$'
    msgADD    db 13,10, '[ADD CONTACT]', 13,10, '$'
    msgVIEW     db 13,10, '[VIEW CONTACTS]', 13,10, '$'
    msgSEARCH    db 13,10, '[SEARCH CONTACT]', 13,10, '$'
    msgMODIFY    db 13,10, '[MODIFY CONTACT]', 13,10, '$'
    msgDELETE1    db 13,10, '[DELETE CONTACT]', 13,10, '$' 
    msgFULL     db 13,10, 'THE MEMORY IS FULL , YOU RECHEAD 16 CONTACTS' , 13,10, '$'
    msg_name db 13,10,'ENTER THE NAME :$'
    msg_nmb db 13,10,'ENTER THE NUMBER :$'
    nameis db 13,10,'>NAME:$'
    numberis db '>PHONE NUMBER:$'
    newnumber db 13,10,'ENTER THE NEW PHONE:$' 
    msgDELETE2 db 13,10,'CONTACT DELETED SUCCESSFULLY',13,10,'$'
    notfound  db 13,10,'CONTACT NOT FOUND',13,10,'$' 
    ;DATA STRUCTURE :
    memory db 368 dup(0)
    ;ALLOCATING A MEMORY OF 368 BYTES
    ;23 BYTES FOR EACH CONTACT
    ;10 BYTES FOR THE NAME + 1 FOR THE '$' TO DETECT THE END OF THE STRING
    ;10 BYTES FOR THE PHONE NUMBER + 1 FOR THE '$' TO DETECT THE END OF THE STRING
    ;1 BYTES AS EXIST FLAG (1 IF EXISTS 0 IF EMPTY)     
DATA ENDS
CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,SS:STACK
MAIN:
    MOV AX, DATA
    MOV DS, AX
START:
    CALL CLEARSCR
    CALL DISPLAYMENU    
    MOV AH, 01h
    INT 21h
    MOV choice, AL
    CALL CLEARSCR
    CMP choice, '1'
    JE ADDCONTACT
    CMP choice, '2'
    JE VIEWCONTACTS
    CMP choice, '3'
    JE SEARCHCONTACT
    CMP choice, '4'
    JE MODIFYCONTACT
    CMP choice, '5'
    JE DELETECONTACT
    CMP choice, '6'
    JE EXIT
Invalide:
    LEA DX, msgINVALID
    MOV AH, 09h  
    INT 21h
    CALL WAITKEY            
ADDCONTACT:
    ; Display [ADD CONTACT]
    LEA DX, msgADD
    MOV AH, 09h
    INT 21h
    ; Search for an empty slot
    MOV SI, OFFSET memory
    MOV CX, 16; Max 16 contacts
FindEmptySlot:
    MOV AL, [SI]; Read existence byte
    CMP AL, 0
    JE SlotFound; Found an empty slot
    ADD SI, 23; Move to next contact(Each contact has 23 bytes)
    LOOP FindEmptySlot
    ;If no slot found
    LEA DX, msgFULL; Reuse invalid message for "THE MEMORY IS FULL , YOU RECHEAD 16 CONTACTS"
    MOV AH, 09h
    INT 21h
    CALL WAITKEY
    JMP START
SlotFound:
    ; Mark slot as occupied
    MOV BYTE PTR [SI], 1
    INC SI; Move SI to name
    ;Ask for name
    LEA DX, msg_name
    MOV AH, 09h
    INT 21h
    ;Input name (max 10 chars)
    MOV DI, SI
    MOV CX, 10; Max 10 characters for name
ReadName:
    MOV AH, 01h
    INT 21h
    CMP AL, 13; Enter pressed(Name can be less than 10 chars)
    JE EndNameInput
    MOV [DI], AL
    INC DI
    LOOP ReadName
EndNameInput:
    MOV BYTE PTR [DI], '$'  ; End of name with $(in that extra byte)
    ;Move SI to number
    ADD SI, 11; 10 name + 1 $ 
    ; Ask for number
    LEA DX, msg_nmb
    MOV AH, 09h
    INT 21h
    ; Input number (10 digits)
    MOV DI, SI
    MOV CX, 10
ReadNumber:
    MOV AH, 01h
    INT 21h
    CMP AL, 13
    JE EndNumberInput
    MOV [DI], AL
    INC DI
    LOOP ReadNumber
EndNumberInput:
    MOV BYTE PTR [DI], '$';End of number with $
    ; Finished adding
    CALL WAITKEY
    JMP START
VIEWCONTACTS:
    ; Display [VIEW CONTACTS]
    LEA DX, msgVIEW
    MOV AH, 09h
    INT 21h
    ;Initialize pointer to the start of memory
    MOV SI, OFFSET memory
    MOV CX, 16; We have 16 contacts maximum
NextContact:
    ;Check if this contact exists
    MOV AL, [SI]; Read existence byte
    CMP AL, 1
    JNE SkipContact; If not 1, skip this contact
    ; Contact exists, display it (=1)
    ; Display name
    LEA DX, nameis; Message: "NAME:"
    MOV AH, 09h
    INT 21h
    ; Load name
    MOV DX, SI
    ADD DX, 1;Move past existence byte to name
    MOV AH, 09h
    INT 21h
    CALL NEWLINE
    ; Display number
    LEA DX, numberis; Message: "PHONE NUMBER:"
    MOV AH, 09h
    INT 21h
    ; Load number
    MOV DX, SI
    ADD DX, 12; Move past existence + 10 name + 1 $
    MOV AH, 09h
    INT 21h  
    CALL NEWLINE
SkipContact:
    ; Move to next contact slot
    ADD SI, 23; Each contact uses 23 bytes
    LOOP NextContact; Repeat for all contacts
    ; After displaying all, wait for key and return to menu
    CALL WAITKEY
    JMP START
SEARCHCONTACT:
    ; Display [Rechercher Contact]
    LEA DX, msgSEARCH
    MOV AH, 09h
    INT 21h
    ; Ask for the name to search
    LEA DX, searchName
    MOV AH, 09h
    INT 21h
    ; Read the name to search into a buffer
    MOV DI, OFFSET searchBuffer
    MOV CX, 10; Maximum 10 characters for name
ReadSearchName:
    MOV AH, 01h
    INT 21h
    CMP AL, 13; Enter pressed
    JE EndSearchNameInput
    MOV [DI], AL
    INC DI
    LOOP ReadSearchName
EndSearchNameInput:
    MOV BYTE PTR [DI], '$'; End the input string with $
    ; Now search for the name
    MOV SI, OFFSET memory
    MOV CX, 16; 16 contacts maximum
SearchLoop:
    ; Check if contact exists
    MOV AL, [SI]
    CMP AL, 1; Comparing with the existing byte
    JNE SkipSearchContact   ; If not existing,skip
    ; Compare names
    PUSH CX; Save CX
    PUSH SI; Save SI
    LEA DI, searchBuffer; DI points to the entered name
    MOV BX, SI
    ADD BX, 1; BX points to contact's name
CompareNameLoop:
    MOV AL, [DI]; Character from user input
    MOV DL, [BX]; Character from stored name
    CMP AL, '$'             
    JE NameMatched; End of input name and so far all matched
    CMP AL, DL
    JNE NameNotMatched;If matches continue
    INC DI
    INC BX
    JMP CompareNameLoop
NameMatched:
    ; Name matched, display the phone number
    ; Display a message
    LEA DX, searchNumber
    MOV AH, 09h
    INT 21h
    ; Display the number
    MOV DX, SI
    ADD DX, 12 ; Move to the number (after exist + name + $)
    MOV AH, 09h
    INT 21h
    ; New line
    MOV DL, 13
    MOV AH, 02h
    INT 21h
    MOV DL, 10
    MOV AH, 02h
    INT 21h
    POP SI
    POP CX
    CALL WAITKEY
    JMP START
NameNotMatched:
    POP SI
    POP CX
SkipSearchContact:
    ADD SI, 23 ; Move to next contact
    LOOP SearchLoop
    ; If not found
    LEA DX, notfound ; Display "not found" message
    MOV AH, 09h
    INT 21h
    CALL WAITKEY
    JMP START
MODIFYCONTACT:
    ; Display [Modifier Contact]
    LEA DX, msgMODIFY
    MOV AH, 09h
    INT 21h
    ; Ask the user to input the name
    LEA DX, msg_name
    MOV AH, 09h
    INT 21h
    ; Read the name into searchBuffer
    MOV DI, OFFSET searchBuffer
    MOV CX, 10
ReadModifyName:
    MOV AH, 01h
    INT 21h
    CMP AL, 13; Enter key
    JE EndModifyNameInput
    MOV [DI], AL
    INC DI
    LOOP ReadModifyName
EndModifyNameInput:
    MOV BYTE PTR [DI], '$'; End input with $
    ; Now search for the contact
    MOV SI, OFFSET memory
    MOV CX, 16; 16 contacts to check
SearchModifyLoop:
    MOV AL, [SI]; Check if contact exists
    CMP AL, 1
    JNE SkipModifyContact
    PUSH CX
    PUSH SI
    LEA DI, searchBuffer
    MOV BX, SI
    ADD BX, 1; BX points to contact's name
CompareModifyNameLoop:
    MOV AL, [DI]
    MOV DL, [BX]
    CMP AL, '$'
    JE ModifyFound
    CMP AL, DL
    JNE ModifyNotFound
    INC DI
    INC BX
    JMP CompareModifyNameLoop
ModifyFound:
    ; Contact found, ask for the new number
    LEA DX, newnumber
    MOV AH, 09h
    INT 21h
    ; Read the new number directly into memory
    MOV DI, SI
    ADD DI, 12; Move to number part
    MOV CX, 10; 10 digits expected
ReadNewNumber:
    MOV AH, 01h
    INT 21h
    CMP AL, 13  ; Enter ?
    JE EndReadNewNumber
    MOV [DI], AL
    INC DI
    LOOP ReadNewNumber
EndReadNewNumber:
    MOV BYTE PTR [DI], '$'  ; Mark the end of number string
    POP SI
    POP CX
    CALL WAITKEY
    JMP START
ModifyNotFound:
    POP SI
    POP CX
SkipModifyContact:
    ADD SI, 23
    LOOP SearchModifyLoop
    ; If not found
    LEA DX, msgINVALID
    MOV AH, 09h
    INT 21h
    CALL WAITKEY
    JMP START
DELETECONTACT:
    ; Display [DELETE CONTACT]
    LEA DX, msgDELETE1
    MOV AH, 09h
    INT 21h
    ; Ask the user for the name to delete
    LEA DX, msg_name
    MOV AH, 09h
    INT 21h
    ; Read the name into searchBuffer
    MOV DI, OFFSET searchBuffer
    MOV CX, 10
ReadDeleteName:
    MOV AH, 01h
    INT 21h
    CMP AL, 13  ; Enter key
    JE EndDeleteNameInput
    MOV [DI], AL
    INC DI
    LOOP ReadDeleteName
EndDeleteNameInput:
    MOV BYTE PTR [DI], '$'  ; Terminate input with $
    ; Now search for the contact
    MOV SI, OFFSET memory
    MOV CX, 16  ; 16 contacts max
SearchDeleteLoop:
    MOV AL, [SI]  ; Check if contact exists
    CMP AL, 1
    JNE SkipDeleteContact
    PUSH CX
    PUSH SI
    LEA DI, searchBuffer
    MOV BX, SI
    ADD BX, 1   ; BX points to contact's name
CompareDeleteNameLoop:
    MOV AL, [DI]
    MOV DL, [BX]
    CMP AL, '$'
    JE ContactToDeleteFound
    CMP AL, DL
    JNE ContactNotFoundDelete
    INC DI
    INC BX
    JMP CompareDeleteNameLoop
ContactToDeleteFound:
    ; Contact found, delete it by setting existence byte to 0
    MOV BYTE PTR [SI], 0
    ;clear the name and number areas
    MOV CX, 22 ; 10 name + 1 $ + 10 number + 1 $
    MOV DI, SI
    INC DI ; Move to the name field
ClearContactData:
    MOV BYTE PTR [DI], 0
    INC DI
    LOOP ClearContactData
    POP SI
    POP CX
    ; Show a confirmation message 
    LEA DX, msgDELETE2
    MOV AH, 09h
    INT 21h
    CALL WAITKEY
    JMP START
ContactNotFoundDelete:
    POP SI
    POP CX
SkipDeleteContact:
    ADD SI, 23
    LOOP SearchDeleteLoop
    ; If no contact found
    LEA DX, notfound
    MOV AH, 09h
    INT 21h
    CALL WAITKEY
    JMP START
EXIT:
    MOV AH, 4Ch
    INT 21h
DISPLAYMENU PROC    
    LEA DX, menu
    MOV AH, 09h
    INT 21h
    RET
DISPLAYMENU ENDP
CLEARSCR PROC
    mov ah, 0
    mov al, 3
    int 10h
    RET
CLEARSCR ENDP 
WAITKEY PROC
    MOV AH, 08h
    INT 21h
    JMP START
    RET     
WAITKEY ENDP
NEWLINE PROC
    MOV DL, 13
    MOV AH, 02h
    INT 21h
    MOV DL, 10
    MOV AH, 02h
    INT 21h
    RET
NEWLINE ENDP
END MAIN