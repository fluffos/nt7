// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m泡沫[2;37;0m[2;37;0m", ({"pao"}));        
        set("gender", "男性");                
        set("long", "我最喜欢的大美女泡泡泡沫。[2;37;0m
它是今夕的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jinxi");
        set("owner_name", "今夕");
        set_temp("owner", "jinxi");
        set_temp("owner_name", "今夕");
        ::setup();
}
