// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "这是一辆公主自行车[2;37;0m
它是小女孩的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xnh");
        set("owner_name", "小女孩");
        set_temp("owner", "xnh");
        set_temp("owner_name", "小女孩");
        ::setup();
}
