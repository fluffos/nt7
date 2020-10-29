#include <ansi.h>
inherit ITEM;

string do_long();
string name,id;
int birthday;

void create()
{
        object me;
        if (this_player())
        {
        me = this_player();
        name=query("name", me);
        id=query("id", me);
        birthday=query("birthday", me);
        }
        set_name("电子表", ({ "watch" }) );
        set("long", (: do_long :) );
        set("unit", "块");
        set("value", 0);

        setup();
}

int query_autoload()
{
        if( id != query("id", this_player()))return 0;
        return 1;
}

void init()
{
        add_action("do_zeng", "zeng");
}

int do_zeng(string arg)
{
        object me, ob, obj;
        string item, target;;

        me = this_player();
        if(!arg||sscanf(arg, "%s to %s", item, target)!=2) return notify_fail("zeng <物品> to <某人>\n");
        obj = present(item, me);
        ob = present(target, environment(me));
        if(!ob) return notify_fail("这里没有这个人。\n");
        if(!obj) return notify_fail("你身上没有这样物品。\n");
        if(obj!=this_object()) return notify_fail("这样东西还是不赠的好。\n");
        if( id != query("id", me))return notify_fail("你不是这个物品的主人，无权转赠！\n");
        name=query("name", ob);
        id=query("id", ob);
        birthday=query("birthday", ob);
        obj->move(ob);
        if( query("id", me) == "wop")message_vision("$N赠给$n一"+query("unit", obj)+query("name", obj)+"。\n",me,ob);
        else message_vision("$N将"+query("name", obj)+"转赠给了$n。\n",me,ob);
        return 1;
}

string do_long()
{
        mixed *local, *birth;
        string ld,lt,gt;
        int h, y;

        local = localtime(time());
        ld = sprintf("%d-%s%d-%s%d", local[5],
                (local[4]<9)?"0":"", local[4]+1,
                (local[3]<10)?"0":"", local[3]);
        h = (local[2]>12)?(local[2]-12):local[2];
        lt = sprintf("%s%d:%s%d:%s%d%s", (h<10)?"0":"", h,
                (local[1]<10)?"0":"", local[1],
                (local[0]<10)?"0":"", local[0],
                (local[2]>12)?"pm":"am"
                );

        birth = localtime(birthday);
        if( (local[4]>birth[4]) || ((local[4]==birth[4])&&(local[3]>=birth[3])) )
                y = local[5];
        else y = local[5] - 1;
        gt = CHINESE_D->chinese_number(y/1000) + CHINESE_D->chinese_number((y/100)%10)
                + CHINESE_D->chinese_number((y/10)%10) + CHINESE_D->chinese_number(y%10)
                + "年" + CHINESE_D->chinese_number(birth[4]+1) + "月"
                + CHINESE_D->chinese_number(birth[3]) + "日";

        printf("这是一块精致的电子表，表上显示现在的时间是：\n\n");
        printf(HIY"\t\t"HBBLU"┏--------------┓\n"NOR);
        printf(HIY"\t\t"HBBLU"┃  "HIR"%s"YEL"  ┃\n"NOR, ld);
        printf(HIY"\t\t"HBBLU"┃  "HIR"%s"YEL"  ┃\n"NOR, lt);
        printf(HIY"\t\t"HBBLU"┗--------------┛\n"NOR);
        printf("\n表的背后刻着一行小字：\n\n");
        printf(HIY"\t赠%s：\n\n"NOR, name);
        printf(HIR"\t\t祝天天快乐!\n\n"NOR);
        printf(HIB"\t\t\t\t\t夜辰(nightstar)赠于\n"NOR);
        printf(HIB"\t\t\t\t\t%s\n"NOR, gt);
        return "";
}
