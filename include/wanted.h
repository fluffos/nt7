
 int is_wanted(object me)
 {
        if (me->query_condition("killer")) {
                notify_fail("你还是了结完江湖恩怨再说吧。\n");
                return 1;
        }
        if (sizeof(filter_array(deep_inventory(me), (: userp :)))) {
                notify_fail("你想贩卖人口啊。\n");
                return 1;
        }
        return 0;
 }

