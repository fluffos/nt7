// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("嗨嗨[2;37;0m[2;37;0m", ({"himi"}));        
        set("gender", "女性");                
        set("long", "嗨[2;37;0m
它是黄尚的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huang");
        set("owner_name", "黄尚");
        set_temp("owner", "huang");
        set_temp("owner_name", "黄尚");
        ::setup();
}
