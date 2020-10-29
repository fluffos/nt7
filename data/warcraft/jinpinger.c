// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大吉吉[2;37;0m[2;37;0m", ({"bigjb"}));        
        set("gender", "男性");                
        set("long", "一个用来。。。。。。的怪兽[2;37;0m
它是金瓶儿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jinpinger");
        set("owner_name", "金瓶儿");
        set_temp("owner", "jinpinger");
        set_temp("owner_name", "金瓶儿");
        ::setup();
}
