// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m玄武大帝[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "女性");                
        set("long", "厉害的神兽[2;37;0m
它是张云祥的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zjues");
        set("owner_name", "张云祥");
        set_temp("owner", "zjues");
        set_temp("owner_name", "张云祥");
        ::setup();
}
