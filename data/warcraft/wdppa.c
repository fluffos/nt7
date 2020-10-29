// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啊[2;37;0m[2;37;0m", ({"olo"}));        
        set("gender", "女性");                
        set("long", "啊[2;37;0m
它是武当师一的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wdppa");
        set("owner_name", "武当师一");
        set_temp("owner", "wdppa");
        set_temp("owner_name", "武当师一");
        ::setup();
}
