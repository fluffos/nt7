#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        string tmp;
        int no;
        set_name(CYN "玄铁剑" NOR,({"xuantie jian","xuantie","jian"}));
        set_weight(140000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "柄");
                set("long", "重剑无锋，大巧不工。这柄剑是天外玄铁所铸，无刃无锋，拙钝无比。然而，裂金玉如破腐土，无坚不摧。神雕侠杨过昔年凭它名扬天下。\n");
                set("material", "steel");
                set("no_drop", "如此宝贵的武器再世难求啊。\n");
                set("no_give", "送人？亏你想的出来！\n");
                set("no_put", "珍惜它吧。\n"); 
                set("no_sell", "卖？这样的神兵用来卖？你是不是快饿死了？\n");   
                set("wield_msg", CYN "$N缓缓从背后拔出玄铁剑，天地间顿时一片阴霾，隐隐有雷声滚动。\n" NOR);
                set("unwield_msg", CYN "$N神色凝重，将玄铁剑纳入背后的布包中，霎时间风雷隐隐。\n" NOR);
       }
// modified by chacha
       init_sword(70);
       setup();
// following 2 lines was added by chacha
       sscanf(file_name(),"%s#%d",tmp,no);
       if(no>0) destruct(this_object()); 
}

void init()
{
        add_action("do_get","get");
// modified by chacha
        set("weapon_prop/damage",query("max_neili", this_player())/2);
}

int do_get(string arg)
{
        object me,ob;
        me=this_player();
        ob=this_object(); 

    if( !arg ) return notify_fail("你要捡起什麽东西？\n");
        if (arg=="xuantie jian" || arg=="xuantie" || arg=="jian" ) 
         {
       if( query("str", me)<31 )
        return notify_fail("你臂力不足，拿不动玄铁剑。\n");
        else
        write("好一把绝世的名剑！\n");
        ob->move(me);
        return 1;
         }
}

void owner_is_killed()
{
       destruct(this_object());
}