size = 3
client_list = [None] * size

def add_client():
    client_id = int(input("Client ID: "))
    name = input("Client Name: ")
    telephone = input("Client Telephone: ")
    client_details = [client_id, name, telephone]
    index = client_id % size

    for i in range(size):
        if client_list[index] is None:
            client_list[index] = client_details
            print("Added client at index", index, client_details)
            return
        else:
            index = (index + 1) % size
    print("Client list is full. Could not add client.")

def search_client():
    client_id = int(input("Client ID to search: "))
    index = client_id % size

    for i in range(size):
        if client_list[index] is not None and client_list[index][0] == client_id:
            print("Client found at index", index, client_list[index])
            return
        index = (index + 1) % size
    print("Client not found.")

def delete_client():
    client_id = int(input("Client ID to delete: "))
    index = client_id % size

    for i in range(size):
        if client_list[index] is not None and client_list[index][0] == client_id:
            client_list[index] = None
            print("Client deleted at index", index)
            return
        index = (index + 1) % size
    print("Client not found.")

# Main program loop
while True:
    print("\n\t1: Add Client")
    print("\t2: Search Client")
    print("\t3: Delete Client")
    print("\t4: Exit")
    ch = int(input("Enter your choice: "))

    if ch == 1:
        add_client()
    elif ch == 2:
        search_client()
    elif ch == 3:
        delete_client()
    elif ch == 4:
        print("End of Program")
        break
    else:
        print("Invalid choice. Try again.")