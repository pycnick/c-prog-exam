#include <stdio.h>
#include <stdlib.h>

struct list
{
	void * data;
	struct list * next;
};


struct list * list_read(FILE* file)
{
	struct list * head = malloc(sizeof(struct list));
	struct list * mem = head;
	char * string = malloc(sizeof(char) * 32);

	while(fscanf(file, "%s", string) != EOF)
	{
		mem->data = string;
		struct list * temp = malloc(sizeof(struct list));
		mem->next = temp;
		mem = temp;
		string = malloc(sizeof(char) * 32);
	}
	free(string);
	mem->next = NULL;

	return head;
}

void list_print(struct list * head)
{
	while(head->next != NULL)
	{
		printf("%s\n", head->data);
		head = head->next;
	}
		
}

void free_list(struct list * head)
{
	while(head->next != NULL)
	{
		struct list * mem = head;
		free(mem->data);
		head = head->next;
		free(mem);
	}

	free(head);
}


int main(void)
{
	FILE* file = fopen("in.txt", "r");

	struct list * head = list_read(file);

	list_print(head);

	free_list(head);

	return 1;
}