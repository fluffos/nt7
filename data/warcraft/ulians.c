// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火行[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "嘿嘿[2;37;0m
它是楚歌的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ulians");
        set("owner_name", "楚歌");
        set_temp("owner", "ulians");
        set_temp("owner_name", "楚歌");
        ::setup();
}
