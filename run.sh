#!/bin/bash

echo "======================================"
echo "       CS509 LAB ASSIGNMENTS"
echo "======================================"
echo "1. Lab Assignment 01"
echo "2. Lab Assignment 02"
echo "3. Exit"
echo "======================================"

read -p "Enter your choice : " choice

case $choice in

    1)
        (
            cd Lab_Assignment_01
            ./run
        )
        ;;

    2)
        (
            cd Lab_Assignment_02
            ./run
        )
        ;;

    3)
        echo "Exiting..."
        exit 0
        ;;

    *)
        echo "[ERROR] Invalid Choice."
        ;;
esac