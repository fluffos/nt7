// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是丸聊聊的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wanll");
        set("owner_name", "丸聊聊");
        set_temp("owner", "wanll");
        set_temp("owner_name", "丸聊聊");
        ::setup();
}
