// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m看剑[2;37;0m[2;37;0m", ({"qiji"}));        
        set("gender", "男性");                
        set("long", "梦回吹角连营[2;37;0m
它是辛弃疾的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xinqiji");
        set("owner_name", "辛弃疾");
        set_temp("owner", "xinqiji");
        set_temp("owner_name", "辛弃疾");
        ::setup();
}
