// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"zxcc"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是裘雄风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ahsdpvlhf");
        set("owner_name", "裘雄风");
        set_temp("owner", "ahsdpvlhf");
        set_temp("owner_name", "裘雄风");
        ::setup();
}
