// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("嗷嗷嗷叫[2;37;0m[2;37;0m", ({"aaaaa"}));        
        set("gender", "女性");                
        set("long", "嗷嗷嗷叫[2;37;0m
它是啊四的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "chickend");
        set("owner_name", "啊四");
        set_temp("owner", "chickend");
        set_temp("owner_name", "啊四");
        ::setup();
}
