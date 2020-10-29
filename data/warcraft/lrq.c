// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哈哈[2;37;0m[2;37;0m", ({"kkkkk"}));        
        set("gender", "女性");                
        set("long", "哈哈大笑[2;37;0m
它是魑魅魍魉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lrq");
        set("owner_name", "魑魅魍魉");
        set_temp("owner", "lrq");
        set_temp("owner_name", "魑魅魍魉");
        ::setup();
}
