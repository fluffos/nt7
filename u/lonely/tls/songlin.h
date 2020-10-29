int valid_leave(object me, string dir)
{
        if (dir == "west")
         me->add_temp("mark/step",1);
        if (dir == "south")
          me->add_temp("mark/steps",1);
        if (dir == "east")
          me->add_temp("mark/step",-1); 
        if (dir == "north")
          me->add_temp("mark/steps",-1);

        if (me->query_temp("mark/step") == -6&&me->query_temp("mark/steps") == -7&&random(me->query("int"))>20)
         {
            me->move(__DIR__"xdt");
            me->delete_temp("mark/steps");
            me->delete_temp("mark/step");
             return notify_fail("你正走着，透过树枝，隐约发现前面有片空地，你拨开树枝钻了过去。\n");
         }  
        if (me->query_temp("mark/steps") == -6&&me->query_temp("mark/step") == 5)
         {
            me->move(__DIR__"lsy");
            me->delete_temp("mark/steps");
            me->delete_temp("mark/step");
             return notify_fail("你正走着，突然发现前面有一间小木屋,你不由的走了过去。\n");
         }  
     if (me->query_temp("mark/steps") > 10)
            {  
           me->move(__DIR__"road7");
           me->delete_temp("mark/steps");
           me->delete_temp("mark/step");
 return notify_fail("你筋疲力尽,终于走出了松林。\n");

        }
           
        return ::valid_leave(me, dir);
}

