// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m九天凤凰[2;37;0m[2;37;0m", ({"fenghuang"}));        
        set("gender", "女性");                
        set("long", "九天凤凰[2;37;0m
它是七八的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zxil");
        set("owner_name", "七八");
        set_temp("owner", "zxil");
        set_temp("owner_name", "七八");
        ::setup();
}
