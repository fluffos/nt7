// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小虫子[2;37;0m[2;37;0m", ({"icq"}));        
        set("gender", "女性");                
        set("long", "喵呜[2;37;0m
它是小阿的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiao");
        set("owner_name", "小阿");
        set_temp("owner", "xiao");
        set_temp("owner_name", "小阿");
        ::setup();
}
