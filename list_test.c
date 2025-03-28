FILE *f = fopen("out.tmp", "w+");
struct linked_list ll = {.head = NULL};
insert_at_head(&ll, 10);
insert_at_head(&ll, 20);
insert_at_head(&ll, 30);
dump_list(f, ll);

insert_at_tail(&ll, 100);
insert_at_tail(&ll, 200);
insert_at_tail(&ll, 300);
dump_list(f, ll);

fprintf(f, "%d\n", (int)remove_from_head(&ll));
fprintf(f, "%d\n", (int)remove_from_head(&ll));

dump_list(f, ll);
fprintf(f, "%d\n", (int)remove_from_tail(&ll));
dump_list(f, ll);
fprintf(f, "%d\n", (int)remove_from_tail(&ll));
dump_list(f, ll);
fprintf(f, "%d\n", (int)remove_from_head(&ll));
dump_list(f, ll);
fprintf(f, "%d\n", (int)remove_from_tail(&ll));
dump_list(f, ll);
fprintf(f, "%d\n", (int)remove_from_tail(&ll));
dump_list(f, ll);
fprintf(f, "%d\n", (int)remove_from_head(&ll));

dump_list(f, ll);
free_list(ll);

fclose(f);