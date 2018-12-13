#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 20

struct DataItem {
   int port;
   int key;
};

struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
   return key % SIZE;
}

struct DataItem *search(int key) {
   //get the hash
   int hashIndex = hashCode(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {

      if(hashArray[hashIndex]->key == key)
	 return hashArray[hashIndex];

      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   return NULL;
}

void insert(int key,int port) {
   int hashIndex;
    struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->port = port;
   item->key = key;

   //get the hash
   hashIndex = hashCode(key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   hashArray[hashIndex] = item;
}

struct DataItem* delete(struct DataItem* item) {
   int key = item->key;

   //get the hash
   int hashIndex = hashCode(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {

      if(hashArray[hashIndex]->key == key) {
	 struct DataItem* temp = hashArray[hashIndex];

	 //assign a dummy item at deleted position
	 hashArray[hashIndex] = dummyItem;
	 return temp;
      }

      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   return NULL;
}

void display() {
   int i = 0;

   for(i = 0; i<SIZE; i++) {

      if(hashArray[i] != NULL)
	 printf(" (%d,%d)\n",hashArray[i]->key,hashArray[i]->port);
      else
	 printf("--\n");
   }

   printf("\n");
}

int main() {
    int ch, key, count = 1, val;
   dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
   dummyItem->port = -1;
   dummyItem->key = -1;

   insert(189751, 2760);
   insert(146822, 4731);
   insert(424782, 7963);
   insert(487265, 7692);
   insert(127552, 4590);
   insert(147391, 2071);
   insert(172843, 7000);
   insert(134541, 4586);
   insert(374452, 2001);

   display();
   while (count) {
   printf("Enter 1: Insert 2. Search, 3: Delete, 4: Display, 5: Exit\n");
	scanf("%d",&ch);
	switch (ch) {
		case 1: printf("Enter the mac address  and port no.\n");
			scanf("%d",&key);
			scanf("%d", &val);
			insert(key, val);
			break;
		case 2: printf("Enter the key to be searched\n");
				scanf("%d",&key);
				item = search(key);
				if(item != NULL) {
			printf("Element found and its portnumber is: %d\n", item->port);
				} else {
			printf("Element not found\n"); }
				  break;
		case 3: printf("Enter the key to be deleted\n");
				scanf("%d",&key);
				item = search(key);
				if(item != NULL) {
			printf("Element with portnumber: %d is deleted\n", item->port);
				} else {
			printf("Element not found\n");
				}
				delete(item);
				break;
		case 4: display(); break;
		case 5: count = 0; break;
   }
   }
   return 0;
}
