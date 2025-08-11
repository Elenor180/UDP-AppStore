# UPD AppStore

UPD AppStore is a Qt-based desktop application designed for managing customer purchases and broadcasting transaction data over a local network in XML format.  
It includes integrated transaction tracking, a store receiver for real-time data monitoring, and an in-app help system.
Demonstrating Cloud Computing practices

## Features
- Add new customers with name and surname.
- Select items to purchase using intuitive spin boxes.
- Record transactions and view them in a tree display.
- Broadcast transaction data as XML to a store receiver.
- Local network integration between the store app and store receiver.
- Built-in help instructions.

## How to Use

1. **Add Customer**  
   Enter your name and surname, then click **Add Customer**.

2. **Select Items**  
   Choose the desired items using the two spin boxes.

3. **Add Item**  
   Click **Add Item** to include the selected items in your transaction.

4. **Record Transaction**  
   Click **Record Transaction** to save your purchase.  
   The recorded transaction will appear in the drop-down tree view.  
   Confirm the tree contains your record.

5. **Broadcast Data**  
   Click **Broadcast** to send the transaction data as XML.  
   Ensure the **store receiver** is open and running on the same machine as the store app.

6. **Verify Broadcast**  
   The store receiver listens for XML data from the store app.  
   Confirm that you see the data received in XML format.

7. **Help**  
   Click **Help** in the application for in-app usage instructions.

## Requirements
- Qt framework (tested with Qt 6.8)
- C++ compiler supported by Qt
- Local network connection for broadcasting and receiving data
