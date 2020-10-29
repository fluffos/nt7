// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("及时雨[2;37;0m[2;37;0m", ({"lssj"}));        
        set("gender", "男性");                
        set("long", "及时雨[2;37;0m
它是玉麒麟的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lyuqilin");
        set("owner_name", "玉麒麟");
        set_temp("owner", "lyuqilin");
        set_temp("owner_name", "玉麒麟");
        ::setup();
}
