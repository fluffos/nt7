// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m吴裕兰[2;37;0m[2;37;0m", ({"yulan"}));        
        set("gender", "女性");                
        set("long", "乳头很大，胸部很挺，阴毛厚而密[2;37;0m
它是张居正的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "nandi");
        set("owner_name", "张居正");
        set_temp("owner", "nandi");
        set_temp("owner_name", "张居正");
        ::setup();
}
