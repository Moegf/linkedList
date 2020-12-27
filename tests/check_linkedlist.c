#include <stdlib.h>
#include <stdio.h>
#include "check.h"
#include "../src/linkedlist.h"

int sum(int a, int b)
{
    return a + b;
}

int difference(int a, int b)
{
    return a - b;
}

int product(int a, int b)
{
    return a * b;
}

int square(int a)
{
    return a * a;
}

START_TEST(test_linked_list)
{
    int l = 5;
    linkedList *list = leaf(1);
    int array[] = {1, 2, 3, 4, 5};
    linkedList *listFromArray = fromArray(array, 5);
    linkedList *empty = fromArray(array, 0);

    for (int i = 2; i <= l; i++)
    {
        append(list, i);
    }

    print(list);

    ck_assert_ptr_eq(empty, NULL);
    ck_assert_int_eq(equals(listFromArray, list), 1);

    int *reArray = toArray(list);

    for (int i = 0; i < l; i++)
    {
        ck_assert_int_eq(array[i], reArray[i]);
    }

    ck_assert_int_eq(length(list), 5);
    ck_assert_int_eq(get(list, 0), 1);
    ck_assert_int_eq(get(list, 3), 4);
    ck_assert_int_eq(get(list, 42), 0);
    ck_assert_int_eq(contains(list, 3), true);
    ck_assert_int_eq(contains(list, 9), false);

    ck_assert_int_eq(foldr(list, sum, 0), 15);
    ck_assert_int_eq(foldr(list, difference, 0), 3);
    ck_assert_int_eq(foldl(list, difference, 0), -15);

    linkedList *copied = copy(list);

    ck_assert_int_eq(equals(list, copied), true);
    ck_assert_int_eq(equals(copied, list), true);

    map(list, square);

    ck_assert_int_eq(get(list, 0), 1);
    ck_assert_int_eq(get(list, 3), 16);

    ck_assert_int_eq(equals(list, create(1, create(4, create(9, create(16, leaf(25)))))), 1);

    ck_assert_int_eq(foldr(list, product, 1), 14400);
    ck_assert_int_eq(equals(list, copied), false);
    ck_assert_int_eq(equals(copied, list), false);

    ck_assert_int_eq(equals(list, create(1, create(4, create(9, create(16, create(25, leaf(36))))))), false);

    keep(list, 9);
    ck_assert_int_eq(equals(list, create(1, create(4, create(9, create(16, leaf(25)))))), true);

    keep(list, 3);
    ck_assert_int_eq(equals(list, create(1, create(4, leaf(9)))), true);

    clear(list);
    clear(copied);
}

Suite *linkedListSuite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("linked list");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_linked_list);
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = linkedListSuite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}