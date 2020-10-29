#include <ansi.h>

void init()
{
       object me = this_player();
       object ob;

       if( !objectp(ob = FUBEN_D->query_maze_mainobj(me)) ) {
             write(HIR "TSR 物件载入出错，请与本站 (admin) 联系。\n" NOR);
             return;
       }

       //if( wizardp(me) || present("dispay serial", me) ) {
       if( userp(me) ) {

                write(HIG "\n房间ID：" + query("room_id") + "\n");
                write(HIG "管理物件分配该房间的序列号：" + query(query("room_id"), ob) +"\n"NOR);
                write(HIG "正确开锁顺序：A、B、C、D\n" NOR);
       }

       add_action("do_move", "move");
}

int do_move(string arg)
{
       object me = this_player();
       object ob;
       string room_id;

       if( !arg || arg != "desk" )
             return notify_fail("你想移动什么？\n");

       if( me->is_busy() || me->is_fighting() )
             return notify_fail("等你忙完了再说吧！\n");

       ob = FUBEN_D->query_maze_mainobj(me);

       if( !objectp(ob) )
             return notify_fail("TSR 物件载入出错，请与巫师联系！\n");

       if( query("lock/unlocked", ob) )
             return notify_fail("机关已经被打开了，这样是多此一举。\n");

       room_id = query("room_id");
       room_id = query(room_id, ob);

       if( !stringp(ob->openlock(me, room_id)) )
             return notify_fail("TSR 数据出错，请与巫师联系！\n");

       me->start_busy(1 + random(2));

       message_vision(HIC "$N" HIC "将石桌用力的旋转，只听得不远处传来"
                      "一阵轰隆隆的像是触动机关的声音。\n" NOR, me);

       return 1;
}
