#include <stdio.h>

struct Student
{
	unsigned int number;
	float score;
	struct Student *next;
};

int main(int argc, char const *argv[])
{
	model();
	return 0;
}

void model()
{
	struct Student a, b, c, *ptr, *head;
	head = &a;
	a.next = &b;
	b.next = &c;
	c.next = NULL;
	ptr = head;
	view(ptr);
}

void view(struct Student *ptr)
{
	printf("Enter student number, score:\n");
	inPutController(ptr);
	outPutController(ptr);
}

void inPutController(struct Student *ptr)
{
	struct Student *original;
	do
	{
		scanf("%u, %f", &ptr->number, &ptr->score);
		ptr = ptr->next;
	} while(ptr != NULL);
}

void outPutController(struct Student *ptr)
{
	do
	{
		printf("Student number: %u, score: %0.2f\n", ptr->number, ptr->score);
		ptr = ptr->next;
	} while(ptr != NULL);
}
