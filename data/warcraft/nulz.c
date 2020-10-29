// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "女性");                
        set("long", "在天的见证之下，集勇气、智慧、;与美丽于一身的强大生物![2;37;0m
它是三文鱼的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "nulz");
        set("owner_name", "三文鱼");
        set_temp("owner", "nulz");
        set_temp("owner_name", "三文鱼");
        ::setup();
}
