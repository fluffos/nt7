// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m黑[2;37;0m[2;37;0m", ({"hql"}));        
        set("gender", "女性");                
        set("long", "黑[2;37;0m
它是将就爱的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jja");
        set("owner_name", "将就爱");
        set_temp("owner", "jja");
        set_temp("owner_name", "将就爱");
        ::setup();
}
