// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "女性");                
        set("long", "火麒麟[2;37;0m
它是无聊的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "waka");
        set("owner_name", "无聊");
        set_temp("owner", "waka");
        set_temp("owner_name", "无聊");
        ::setup();
}
