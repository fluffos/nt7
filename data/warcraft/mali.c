// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m麒麟兽[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "我的座驾[2;37;0m
它是马啸天的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mali");
        set("owner_name", "马啸天");
        set_temp("owner", "mali");
        set_temp("owner_name", "马啸天");
        ::setup();
}
