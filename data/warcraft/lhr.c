// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m小青[2;37;0m[2;37;0m", ({"xql"}));        
        set("gender", "男性");                
        set("long", "身似长蛇麒麟首鲤鱼尾面有长须犄角似鹿有五爪相貌威武[2;37;0m
它是独孤飞虹的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lhr");
        set("owner_name", "独孤飞虹");
        set_temp("owner", "lhr");
        set_temp("owner_name", "独孤飞虹");
        ::setup();
}
