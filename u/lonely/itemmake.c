// itemmake.c 自制道具

#include <dbase.h>
#include <ansi.h>
#include <name.h>
#include <move.h>
#include <command.h>

inherit F_OBSAVE;
inherit F_NOCLONE;

int is_item_make() { return 1; }

#define LEVEL1    5
#define LEVEL2    10
#define LEVEL3    30
#define LEVEL4    100
#define LEVEL5    300
#define LEVEL6    1000
#define LEVEL7    3000
#define LEVEL8    10000
#define LEVEL9    50000
#define MAX_LEVEL       LEVEL9
#define ULTRA_LEVEL     (LEVEL9 + 1)
#define MEMBER_D        "/adm/daemons/memberd"

#define TAOZHUANG_D     "/adm/daemons/taozhuangd"

nosave int *levels = ({ LEVEL1, LEVEL2, LEVEL3, LEVEL4,
                        LEVEL5, LEVEL6, LEVEL7, LEVEL8,
                        LEVEL9 });

nosave int performing  = 0;
nosave int attack_lvl  = 0;
nosave int defense_lvl = 0;
37      static mapping qianghua_level = ([ 
38              "1":       "★", 
39              "2":       "★★", 
40              "3":       "★★★", 
41              "4":       "★★★★", 
42              "5":       "★★★★★", 
43              "6":       "★★★★★★", 
44              "7":       "★★★★★★★", 
45              "8":       "★★★★★★★★", 
46              "9":       "★★★★★★★★★", 
47              "10":      "★★★★★★★★★★", 
48      ]); 

int is_stay_in_room() { return attack_lvl >= ULTRA_LEVEL; }

// n_type 0 为福缘 1 为气运
int f_enchase_points(int n_type);

string chinese_s(mixed arg)
{
      if (! stringp(arg))return "无";
      if (arg == "cold")return HIW "冰";
      if (arg == "fire")return HIR "火";
      if (arg == "magic")return HIY "魔";
      if (arg == "lighting")return HIM "电";
}


// 武器的主人ID - 通过文件的名字来判断
string item_owner()
{
        string owner;
        if (sscanf(base_name(this_object()), ITEM_DIR "%*s/%s-%*s", owner))
                return owner;

        return 0;
}

// 判断该武器是否被当前某人所持有
int is_not_belong_me(object me)
{
        string user;

  user = query("user");
        if (! user || ! sscanf(user, "%*s(" + me->query("id") + ")"))
                return 1;

        return 0;
}

// 武器装备的等级
int weapon_level()
{
        mapping o;
        string *ks;
        int lvl;
        int i;

        lvl = 0;
        o = query("owner");
        if (mapp(o))
        {
                ks = keys(o);
                for (i = 0; i < sizeof(ks); i++)
                        lvl += o[ks[i]];
        }

        lvl /= 100;
        if (lvl > MAX_LEVEL) lvl = MAX_LEVEL;

        if (lvl == MAX_LEVEL && query("magic/power"))
                // 具有魔法属性
                lvl = ULTRA_LEVEL;
        return lvl;
}

// 防御装备的等级
int armor_level()
{
        // More to be added
        return 0;
}

// 武器装备的长描述
string weapon_long()
{
        string  n;
        mapping c;
        int type;
        int k;
        int lvl;
        string tessera_name;
        string result;
        int enchase_number;
        mixed enchase_objects;
        string* key_objects;
        int i, enchase_points;

        c = query("combat");
        n = query("unit") + name();
        if (! c)
                return "这" + n + "显然还没有饮过人血，上面纯洁无暇。\n";
        k = c["MKS"] + c["PKS"];

        if (c["WPK_GOOD"] < k / 2 &&
            c["WPK_BAD"]  < k / 2)
                type = 0;
        else
        if (c["WPK_GOOD"] > c["WPK_BAD"] * 2)
                type = -1;
        else
                type = 1;

        if (c["MKS"] + c["PKS"] < 10)
                return "这" + n + "看来已经用过人血开祭，上面隐现血痕。\n";

        attack_lvl = weapon_level();
        lvl = sizeof(levels);
        while (--lvl)
                if (attack_lvl >= levels[lvl])
                        break;
        lvl++;

        switch (type)
        {
        case 1:
                if (attack_lvl >= ULTRA_LEVEL)
                        result = HIY "它看上去平平常常，没有半点特殊，只是"
                                 "隐隐的让人感到那不凡的气质。\n" NOR;
                else
                if (attack_lvl >= MAX_LEVEL)
                        result = HIY "它看上去让人发自内心无限崇敬，一股"
                               "皓然正气悠然长存，颇具帝王风范，君临\n"
                               "天下，威镇诸路凶神恶煞、难道这就是传说中才"
                               "会出现的诸神之" + name() + HIY "？\n" NOR;
                else
                if (attack_lvl >= LEVEL8)
                        result = HIC "一眼望去，你觉得有无数的凶灵在疯狂"
                               "乱舞，哭天抢地，凄烈之极，似乎要重返\n"
                               "人间。你忍不住要长叹一声，昔日凶魔，也难逃死劫。\n" NOR;
                else
                if (attack_lvl >= LEVEL7)
                        result = HIC "它上面附着着不知多少凶魂，无数邪派"
                               "凶魔毙命于下，一股哀气犹然不散，让你\n"
                               "忍不住打了个冷战。\n" NOR;
                else
                if (attack_lvl >= LEVEL6)
                        result = HIR "它看上去令人惊心动魄，这就是名动江湖的" + name() + HIR
                               "，多少凶煞就此毙命，成就人间正义。\n" NOR;
                else
                if (attack_lvl >= LEVEL5)
                        result = HIR "它上面隐隐然透出一股血光，多年以来，许多"
                               "江湖上闻名一时的凶魔都成了" + name() + HIR "下的游魂。\n" NOR;
                else
                if (attack_lvl >= LEVEL4)
                        result = HIW "这就是江湖上著名的神兵之一：" + name() + HIW
                               "，穷凶极恶之徒见此物无不心驰神摇。\n" NOR;
                else
                if (attack_lvl >= LEVEL3)
                        result = HIW "这" + n + HIW "有一股正气散发出来，看来它下面凶魂不少。\n" NOR;
                else
                if (attack_lvl >= LEVEL2)
                        result = RED "这" + n + RED "隐然透出一股正气，"
                               "看来它杀了不少凶恶之徒。\n" NOR;
                else
                if (attack_lvl >= LEVEL1)
                        result = RED "细观之下，刃口有一丝血痕，想必是它杀人不少"
                               "，殷血于此吧！\n" NOR;
                else
                        result = CYN "看得出这" + n + CYN "曾经杀过不少凶恶之徒。\n" NOR;
                break;

        case -1:
                if (attack_lvl >= ULTRA_LEVEL)
                        result = HIR "它看上去平平常常，没有半点特殊，但是"
                                 "不知为何却总是让人感到有些不安。\n" NOR;
                else
                if (attack_lvl >= MAX_LEVEL)
                        result = HIR "它看上去让人打心底泛出阵阵寒意，隐"
                               "隐然上面似乎附着着无数冤魂，但是全然\n被这" + n + HIR
                               "上面的杀气所制，难道这就是传说中才会出现的邪神之" + name() + HIR
                               "？\n" NOR;
                else
                if (attack_lvl >= LEVEL8)
                        result = HIC "一眼望去，你觉得有无数的冤魂向你扑"
                               "来，哭天抢地，凄烈之极，你忍不住打了\n"
                               "个寒战，不敢再看第二眼。\n" NOR;
                else
                if (attack_lvl >= LEVEL7)
                        result = HIC "它上面附着着不知多少冤魂，无数高手"
                               "饮恨于下，一股怨气直冲霄汉，让你忍不\n"
                               "住打了个冷战。\n" NOR;
                else
                if (attack_lvl >= LEVEL6)
                        result = HIW "它看上去令人惊心动魄，这就是名动江湖的" + name() + HIW
                               "，不知多少英雄就此饮恨。\n" NOR;
                else
                if (attack_lvl >= LEVEL5)
                        result = HIW "它上面隐隐然透出一股血光，多年以来，许多"
                               "江湖上闻名一时的高手都成了" + name() + HIW "下的游魂。\n" NOR;
                else
                if (attack_lvl >= LEVEL4)
                        result = HIG "这就是江湖上著名的凶器之一：" + name() + HIG
                               "，谁曾想那么多仁人义士饮恨于下。\n" NOR;
                else
                if (attack_lvl >= LEVEL3)
                        result = HIG "这" + n + HIG "有一股戾气散发出来，看来它下面游魂不少。\n" NOR;
                else
                if (attack_lvl >= LEVEL2)
                        result = RED "这" + n + RED "隐然透出一股戾气，看来它杀了不少人。\n" NOR;
                else
                if (attack_lvl >= LEVEL1)
                        result = RED "细观之下，刃口有一丝血痕，想必是它杀人不少"
                               "，殷血于此吧！\n" NOR;
                else
                        result = CYN "看得出这" + n + CYN "曾经杀过不少侠义之士。\n" NOR;
                break;

        default:
                if (attack_lvl >= ULTRA_LEVEL)
                        result = HIC "它看上去平平常常，没有半点特殊，只是一件"
                                 "平凡之极的兵器而已。\n" NOR;
                else
                if (attack_lvl >= MAX_LEVEL)
                        result = HIC "它安然畅意，似乎就要腾空而去，跳出"
                               "三界，不入五行。世间万物，仿佛俱在它\n"
                               "霸气所及之处。冤魂不舞、群邪辟易，无不被这" + n + HIC
                               "上古神兵的霸气所制。\n" NOR;
                else
                if (attack_lvl >= LEVEL8)
                        result = HIM "一眼望去，你觉得有无数的游魂向你扑"
                               "来，哭天抢地，凄烈之极，你顿时觉得它\n"
                               "沉重无比，几乎拿捏不住。\n" NOR;
                else
                if (attack_lvl >= LEVEL7)
                        result = HIM "它上面附着着不知多少游魂，无数正邪"
                               "高手丧命于下，一股怨气哀愁油然不尽，\n"
                               "让你忍不住打了个冷战。\n" NOR;
                else
                if (attack_lvl >= LEVEL6)
                        result = HIR "它看上去令人惊心动魄，这就是名动江湖的" + name() + HIR
                               "，多少正邪高手都难逃此劫，堕入轮回。\n" NOR;
                else
                if (attack_lvl >= LEVEL5)
                        result = HIR "它上面隐隐然透出一股血光，多年以来，许多"
                               "江湖上闻名一时的高手都成了这" + n + HIR "下的游魂。\n" NOR;
                else
                if (attack_lvl >= LEVEL4)
                        result = HIW "这就是江湖上著名的利器之一：" + name() + HIW
                               "，谁能想到那么多高手饮恨于下。\n" NOR;
                else
                if (attack_lvl >= LEVEL3)
                        result = HIW "这" + n + HIW "有一股杀气散发出来，看来它下面游魂不少。\n" NOR;

                else
                if (attack_lvl >= LEVEL2)
                        result = RED "这" + n + RED "隐然透出一股杀气，看来它杀了不少人。\n" NOR;

                else
                if (attack_lvl >= LEVEL1)
                        result = RED "细观之下，刃口有一丝血痕，想必是它杀人不少"
                               "，殷血于此吧！\n" NOR;
                else
                        result = CYN "看得出这" + n + CYN "曾经杀过不少人。\n" NOR;
                break;
        }

        if (attack_lvl == ULTRA_LEVEL)
        {
                if (stringp(tessera_name = query("magic/tessera")))
                        result += "它上面镶嵌着" + tessera_name + "，闪烁着奇异的光芒。\n";
                result += HIY + name() + HIY "的等级：无上神品  LV10\n" NOR;
        } else
        if (lvl)
        {
                result += HIY + name() + HIY "的等级：" + lvl + "/9\n" NOR;

                if (query("magic/imbue_ok"))
                        result += HIM + name() + HIM "已经充分的浸入了，需要"
                                  "镶嵌以充分发挥威力。\n" NOR;
                else
                if ((n = query("magic/imbue")) > 0)
                        result += HIM + name() + HIM "已经运用灵物浸入了" +
                                  chinese_number(n) + "次，正在激发它的潜能。\n" NOR;
        }

              // 扩展镶嵌物品信息
              enchase_objects = query("enchase");
        enchase_points = 0;
              if (! enchase_objects || ! sizeof(enchase_objects))
        {
      enchase_points = 0;
        }
        else
        {
      key_objects = keys(enchase_objects);
                        enchase_number = sizeof(key_objects);
                        for (i = 0; i < enchase_number; i ++)
        enchase_points += enchase_objects[key_objects[i]]["point"];
              }
              // 套装
              result += HIC "--------------套装-------------------\n";
              result += HIC "套装等级：" + TAOZHUANG_D->taozhuang_name(query("taozhuang")) + "\n" NOR;
              result += "-------------------------------------\n";

              result += HIW "坚固修正： " + query("bless") + "\t" NOR;
              result += HIW "攻·防修正：" + sprintf("%d", query("bless") * 2 + enchase_points) + "\n" NOR;
              result += HIW "圣化次数： " + query("bless") + "\t" NOR;
              result += HIW "魔力改善值：" + query("magic/power") + "\n" NOR;
              result += HIW "魔力属性：" + chinese_s(query("magic/type"))  + "\t" NOR;
              result += HIW "人器融合度：" + query("magic/blood") + "\n" NOR;
355                   // 显示强化等级 
356                   if (query("qh_level")) 
357                   { 
358                             result +=  HIY "强化等级：" + qianghua_level[sprintf("%d", query("qh_level"))] + "\n" NOR; 
359                             if (query("weapon_prop/" + item_owner()+ "_potlimit")) 
360                             { 
361                                     if (this_object()->query("armor_type") == "hands") 
362                                             weapon_type = "armor_prop"; 
363                                     else 
364                                             weapon_type = "weapon_prop"; 
365                                     result += sprintf(HIY "%-10s%-12s%-10s%-10s\n" NOR,  
366                                                       "潜能上限：",  
367                                                       sprintf("+%d", query(weapon_type + "/" + item_owner()+ "_potlimit")) + 
368                                                        "%", 
369                                                       "扩展加成：",  
370                                                       sprintf("+%d", 0) + "%"); 
371                             } 
372                   } 
37
        result += HIG "\n---------------镶嵌扩展--------------\n" NOR;
        result += HIW "镶嵌槽使用：  " + sprintf("%d", 1 + enchase_number) + "/" +
                        sprintf("%d", 1 + query("enchase_all")) + "\n";
              result += HIY "---------------镶嵌宝物--------------\n" NOR;
              result += sprintf(HIW "%-16s%-20s%-16s\n\n" NOR,"名称", "ID", "坚固");
        if (! stringp(tessera_name))
       tessera_name = HIR "十级兵器保留槽" NOR;
        result += sprintf(NOR + WHT"%-16s%-20s%-16s\n" NOR, filter_color(tessera_name), "----", "----");
        for (i = 0; i < enchase_number; i ++)
      result = result + sprintf(NOR + WHT "%-16s%-20s%-16d\n" NOR,
                                          enchase_objects[key_objects[i]]["name"],
                                          key_objects[i],
                                          enchase_objects[key_objects[i]]["cur_firm"]);
              result += "-------------------------------------\n";
388                   // 如果存在装备强化效果成功率加成则显示 
389                   if (this_object()->query("suc_points_add")) 
390                             result += HIG "目前该装备强化时可增" + HIY +  
391                                       sprintf("%d", this_object()->query("suc_points_add")) +  
392                                       HIG "%的成功率（仅一次有效）。\n" NOR; 
393                   // 如果存在装备强化效果失败后不掉级则显示 
394                    if (this_object()->query("no_reduce_level")) 
395                             result += HIR "目前该装备强化时失败后不会损失强化等级（仅一次有效）！\n" NOR; 

        return result;
}

string armor_long()
{

        mapping enchase_objects;
        int enchase_points, enchase_number, i;
        string* key_objects;
        string result;

        // 扩展镶嵌物品信息
              enchase_objects = query("enchase");
        enchase_points = 0;
              if (! enchase_objects || ! sizeof(enchase_objects))
        {
      enchase_points = 0;
        }
        else
        {
      key_objects = keys(enchase_objects);
                        enchase_number = sizeof(key_objects);
                        for (i = 0; i < enchase_number; i ++)
        enchase_points += enchase_objects[key_objects[i]]["point"];
              }
              // 套装
              result = "";
              result += HIC "--------------套装-------------------\n";
              result += HIC "套装等级：" + TAOZHUANG_D->taozhuang_name(query("taozhuang")) + "\n" NOR;
              result += "-------------------------------------\n";
              result += HIW "坚固修正： " + query("bless") + "\t" NOR;
              result += HIW "攻·防修正：" + sprintf("%d", query("bless") * 10 + enchase_points) + "\n" NOR;
              result += HIW "圣化次数： " + query("bless") + "\n" NOR;
430                   // 显示强化等级 
431                   if (query("qh_level")) 
432                   { 
433                             result += HIY "强化等级：" + qianghua_level[sprintf("%d", query("qh_level"))] + "\n" NOR; 
434                             if (query("armor_prop/qh_exp")) 
435                             { 
436                                     result += sprintf(HIY "%-10s%-12s%-10s%-10s\n" NOR,  
437                                                       "经验加成：", sprintf("%d", query("armor_prop/qh_exp")) + "%", 
438                                                       "潜能加成：", sprintf("%d", query("armor_prop/qh_pot")) + "%"); 
439                                     result += sprintf(HIY "%-10s%-12s%-10s%-10s\n" NOR,  
440                                                       "体会加成：", sprintf("%d", query("armor_prop/qh_mar")) + "%", 
441                                                       "扩展加成：", sprintf("%d", query("armor_prop/qh_nono")) + "%");                              
442                             } 
443                             if (query("armor_prop/" + item_owner()+ "_potlimit")) 
444                             { 
445                                     result += sprintf(HIY "%-10s%-12s%-10s%-10s\n" NOR,  
446                                                       "潜能上限：",  
447                                                       sprintf("+%d", query("armor_prop/" + item_owner()+ "_potlimit")) + 
448                                                        "%", 
449                                                       "扩展加成：",  
450                                                       sprintf("+%d", 0) + "%"); 
451                             } 
452                   } 

        result += HIG "\n---------------镶嵌扩展--------------\n" NOR;
        result += HIW "镶嵌槽使用：  " + sprintf("%d", enchase_number) + "/" +
                        sprintf("%d", query("enchase_all")) + "\n";
              result += HIY "---------------镶嵌宝物--------------\n" NOR;
              result += sprintf(HIW "%-16s%-20s%-16s\n\n" NOR,"名称", "ID", "坚固");

        for (i = 0; i < enchase_number; i ++)
      result = result + sprintf(NOR + WHT "%-16s%-20s%-16d\n" NOR,
                                          enchase_objects[key_objects[i]]["name"],
                                          key_objects[i],
                                          enchase_objects[key_objects[i]]["cur_firm"]);
              result += "-------------------------------------\n";

    if (this_object()->query("enchase_all") >= 8)
    {
      log_file("srb_bug", base_name(this_object()) + "\n");
    }
466                   // 如果存在装备强化效果成功率加成则显示 
467                   if (this_object()->query("suc_points_add")) 
468                             result += HIG "目前该装备强化时可增" + HIY +  
469                                       sprintf("%d", this_object()->query("suc_points_add")) +  
470                                       HIG "%的成功率（仅一次有效）。\n" NOR; 
471                   // 如果存在装备强化效果失败后不掉级则显示 
472                    if (this_object()->query("no_reduce_level")) 
473                             result += HIR "目前该装备强化时失败后不会损失强化等级（仅一次有效）！\n" NOR; 
474      
475                     if (this_object()->query("enchase_all") >= 11) 
476                     { 
477                             log_file("srb_bug", base_name(this_object()) + "\n"); 
478                     } 
479      

        return result;
}

// 是普通武器装备
int is_weapon()
{
        return stringp(query("skill_type"));
}

// 是空手武器装备
int is_unarmed_weapon()
{
        return query("armor_type") == "hands";
}

// 道具的长描述
string item_long()
{
        if (is_weapon() || is_unarmed_weapon())
                return weapon_long();


        return armor_long();
}

// 武器装备的伤害值
int apply_damage()
{
        int d;
        int p;
        int i, enchase_points, enchase_number, flag_9kong;
        mixed enchase_objects;
        string* key_objects;

        attack_lvl = weapon_level();
        p = query("point");
        d = query("bless") * 10; // 乾坤圣水圣化一次增加2点攻击

        enchase_objects = query("enchase");
  enchase_points = 0;
  flag_9kong = 0;

        if (! enchase_objects || ! sizeof(enchase_objects))
  {
    enchase_points = 0;
  }
  else
  {
    key_objects = keys(enchase_objects);
              enchase_number = sizeof(key_objects);
              for (i = 0; i < enchase_number; i ++)
              {
            enchase_points += enchase_objects[key_objects[i]]["point"];
            // 如果有九孔宝石--海蓝石则做标记
            if (enchase_objects[key_objects[i]]["name"] == "海蓝石")flag_9kong = 1;
            }
        }

  // 镶嵌宝石海蓝石提高整体50%攻击力
  if (flag_9kong)enchase_points = enchase_points + enchase_points / 2;

  if (this_object()->query("enchase_all") >= 11)
  {
    log_file("srb_bug", base_name(this_object()) + "\n");
  }
546      
547             // 在这里添加强化后对镶嵌物品提升的伤害加成 
548             // 强化等级1-10级，每级递增x% 
549             enchase_points = ITEM_D->qianghua_enchase_points("weapon", enchase_points, query("qh_level")); 
550              
551             // 增加潜能加成 
552             if (query("qh_level")) 
553             { 
554                     this_object()->set("weapon_prop/" + item_owner()+ "_potlimit",  
555                                                enchase_number * query("qh_level") / 2); 
556                     this_object()->set("armor_prop/" + item_owner()+ "_potlimit",  
557                                                enchase_number * query("qh_level") / 2);                                        
558             } 
559              


        return d + p + enchase_points * 2;
}

// 防御装备的有效值
int apply_armor()
{
        int d;
        int p;
        int i, enchase_points, enchase_number;
        mixed enchase_objects;
        string* key_objects;

        defense_lvl = armor_level();
        p = query("point");
        d = query("bless") * 10;// 乾坤圣水圣化一次增加2点防御

        enchase_objects = query("enchase");
  enchase_points = 0;
        if (! enchase_objects || ! sizeof(enchase_objects))
  {
    enchase_points = 0;
  }
  else
  {
    key_objects = keys(enchase_objects);
                enchase_number = sizeof(key_objects);
                for (i = 0; i < enchase_number; i ++)
                {
      enchase_points += enchase_objects[key_objects[i]]["point"];
    }
        }
  if (this_object()->query("enchase_all") > 11)
  {
    log_file("srb_bug", base_name(this_object()) + "\n");
  }
  // 10孔镶嵌luhua zhijing 提高伤害40
597             // 披风护腕强化后提升伤害 
598             if (this_object()->query("armor_type") == "wrists"|| this_object()->query("armor_type") == "surcoat") 
599             { 
600                     this_object()->set("armor_prop/damage", 0); 
601                     if (enchase_number > 0) 
602                     { 
603                              
604                             for (i = 0; i < enchase_number; i ++ ) 
605                             { 
606                                     // 是否镶嵌10孔宝石 
607                                     if (enchase_objects[key_objects[i]]["spe_data"]["luhua-zhijing"]) 
608                                     { 
609                                             // LHZJ基本+4000，再计算出强化后的效果 
610                                             this_object()->set("armor_prop/damage", 4000); 
611                                     } 
612                             } 
613                             // 计算披风的强化伤害 
614                             if (this_object()->query("armor_type") == "surcoat") 
615                             { 
616                                     this_object()->add("armor_prop/damage", 
617                                     ITEM_D->qianghua_enchase_points("surcoat", enchase_number, query("qh_level"))); 
618                                      
619                                     // 披风对潜能上限加成 公式：镶嵌数*强化等级/2% 
620                                     if (query("qh_level")) 
621                                     { 
622                                             // 设置了数值，也保持了拥有者有效 
623                                             this_object()->set("armor_prop/" + item_owner()+ "_potlimit",  
624                                                                 enchase_number * query("qh_level") / 2); 
625                                     } 
626                                      
627                             } 
628                             // 计算护腕的伤害 
629                             if (this_object()->query("armor_type") == "wrists") 
630                             { 
631                                     this_object()->add("armor_prop/damage", 
632                                     ITEM_D->qianghua_enchase_points("wrists", enchase_number, query("qh_level"))); 
633      
634                                     /*护腕对经验，潜能和体会的加成 
635                                       -- 经验加成：每级强化等比增加10%的经验加成， 10级强化可 
636                                      增加100%经验加成。 
637                                     -- 潜能加成：前5级强化每级增加4%的潜能加成，6到10级强化 
638                                      每级增加16%的潜能加成。 
639                                      10级强化可增加100%的潜能加成。 
640                                     -- 体会加成：前5级强化每级增加2%的潜能加成，6到10级强化 
641                                     每级增加8%的潜能加成。10级强化可增加50%的潜能加成。 
642                                     */ 
643                                     if (query("qh_level")) 
644                                     { 
645                                             this_object()->set("armor_prop/qh_exp", query("qh_level")*3); 
646                                             if (query("qh_level") <= 5) 
647                                             { 
648                                                     this_object()->set("armor_prop/qh_pot", query("qh_level")*2); 
649                                                     this_object()->set("armor_prop/qh_mar", query("qh_level")*2); 
650                                                     // 设置拥有者 
651                                                     this_object()->set("armor_prop/" + item_owner()+ "_wrists", 1); 
652                                             } 
653                                             else 
654                                             { 
655                                                     this_object()->set("armor_prop/qh_pot",  
656                                                       5 * 2 + (query("qh_level") - 5)*4); 
657                                                     this_object()->set("armor_prop/qh_mar",  
658                                                       5 * 2 + (query("qh_level") - 5)*3); 
659                                                     // 设置拥有者 
660                                                     this_object()->set("armor_prop/" + item_owner()+ "_wrists", 1); 
661                                             } 
662                                             /* 每个镶嵌额外提升 
663                                             每个镶嵌物可额外再提升经验加成3% 
664                                             每个镶嵌物可额外再提升2%的潜能加成 
665                                             每个镶嵌物可额外提升1%的体会加成 
666                                             */ 
667                                             this_object()->add("armor_prop/qh_exp", enchase_number*3); 
668                                             this_object()->add("armor_prop/qh_pot", enchase_number*2); 
669                                             this_object()->add("armor_prop/qh_mar", enchase_number*1); 
670                                              
671                                     } 
672                             } 
673                     } 
674             } 


  /*
  if (find_player("rcwiz") && query("user") == "☆望天涯☆(rcwiz)" )
    tell_object(find_player("rcwiz"), HIR "\narmor_type = " + query("armor_type") + "\n" +
                                          "" NOR );
  */
  if (1 || query("armor_type") == "head") // 根据测试这个地方取不到armor_type
  {
    if (sizeof(key_objects))
    {
      this_object()->set("armor_prop/add_yanjiu", 0);
      this_object()->set("armor_prop/add_jiqu", 0);

      for (i = 0; i < sizeof(key_objects); i ++ )
      {
        // 提高研究效率
        if (enchase_objects[key_objects[i]]["spe_data"]["add_yanjiu"])
          this_object()->add("armor_prop/add_yanjiu",
                             enchase_objects[key_objects[i]]["spe_data"]["add_yanjiu"]);
        // 提高汲取效率
        if (enchase_objects[key_objects[i]]["spe_data"]["add_jiqu"])
          this_object()->add("armor_prop/add_jiqu",
                             enchase_objects[key_objects[i]]["spe_data"]["add_jiqu"]);
      }
    }
  }

        return (d + p + enchase_points * 2) * 6 / 5;
}

// n_type = 0 : 福缘   n_type = 1 ： 气运
int f_enchase_points(int n_type)
{
        int i, enchase_points, enchase_number;
        mixed enchase_objects;
        string* key_objects;

        enchase_objects = query("enchase");
  enchase_points = 0;

        if (! enchase_objects || ! sizeof(enchase_objects))
  {
    enchase_points = 0;
  }
  else
  {
    key_objects = keys(enchase_objects);
                enchase_number = sizeof(key_objects);
                for (i = 0; i < enchase_number; i ++)
                {
                  if (n_type)
                    enchase_points += enchase_objects[key_objects[i]]["qy"];
                  else
                    enchase_points += enchase_objects[key_objects[i]]["fy"];
    }
        }

        return enchase_points;

}

// 进行保存数据的接口函数
mixed save_dbase_data()
{
        mapping data;
        object  user;

        data = ([ "combat" : query("combat"),
                  "owner"  : query("owner"),
                  "magic"  : query("magic"),
                  "consistence" : query("consistence"),
                  "bless"       : query("bless"),
                  "stable"      : query("stable"),
      "enchase"     : query("enchase"),
                  "enchase_all" : query("enchase_all"),
                  "enchase_all_last" : query("enchase_all_last"),// 非会员失效的时候孔的数量
                  //"new_long"         : query("new_long"),             // 可以更改long描述
                  //"new_wear_msg"     : query("new_wear_msg"),         // 可以更改装备时的描述
                  //"new_remove_msg"   : query("new_remove_msg"),       // 可以更改取消装备时的描述
                  "taozhuang"   : query("taozhuang"), // 套装等级
754                       "qh_level"    : query("qh_level"), // 强化等级 
755                       "suc_points_add" : query("suc_points_add"), // 强化成功率增加 
756                       "no_reduce_level": query("no_reduce_level"), // 强化失败不掉等级                 

                  ]);

        if (! (user = environment()))
                data += ([ "user" : query("user") ]);
        else
        if (playerp(user))
                data += ([ "user" : user->name(1) + "(" + user->query("id") + ")" ]);

        return data;
}

// 接受存盘数据的接口函数
int receive_dbase_data(mixed data)
{

        if (! mapp(data))
                return 0;
/*
  // 可以再完成自造兵器后更改long,wear_msg, remove_msg等描述
        if (stringp(data["new_long"]))
                set("new_long", data["new_long"]);
        if (stringp(data["new_wear_msg"]))
                set("new_wear_msg", data["new_wear_msg"]);
        if (stringp(data["new_remove_msg"]))
                set("new_remove_msg", data["new_remove_msg"]);
*/
        if (mapp(data["combat"]))
                set("combat", data["combat"]);

        if (mapp(data["owner"]))
                set("owner", data["owner"]);

        if (mapp(data["magic"]))
                set("magic", data["magic"]);

        if (stringp(data["user"]))
                set("user", data["user"]);

        if (! undefinedp(data["consistence"]))
                set("consistence", data["consistence"]);

        if (intp(data["bless"]))
                set("bless", data["bless"]);

        // 套装
        if (intp(data["taozhuang"]))
                set("taozhuang", data["taozhuang"]);
805             // 强化等级 
806             if (intp(data["qh_level"])) 
807                     set("qh_level", data["qh_level"]);       
808             // 强化增加成功率 
809             if (intp(data["suc_points_add"])) 
810                     set("suc_points_add", data["suc_points_add"]); 
811             // 强化失败不掉等级 
812             if (intp(data["no_reduce_level"])) 
813                     set("no_reduce_level", data["no_reduce_level"]); 
814      

        if (intp(data["stable"]))
                set("stable", data["stable"]);

        if (mapp(data["enchase"]))
                set("enchase", data["enchase"]);

        if (intp(data["enchase_all"]))
    set("enchase_all", data["enchase_all"]);

        if (intp(data["enchase_all_last"]))
    set("enchase_all_last", data["enchase_all_last"]);
}

// 读取存盘的数据
int restore()
{
        int r;

        if (base_name(this_object()) + ".c" == __FILE__)
                return 0;

        r = ::restore();
        set("no_sell", 1);
        set("stable", query("stable"));
        set("bless", query("bless"));
  set("enchaes", query("enchase"));
  set("enchase_all", query("enchase_all"));
  set("taozhuang", query("taozhuang")); // 套装
843             set("qh_level", query("qh_level")); // 强化等级 
844             set("suc_points_add", query("suc_points_add")); // 强化成功率增加 
845             set("no_reduce_level", query("no_reduce_level")); // 强化不掉等级        

/*
  // 设置新long描述
  if (stringp(query("new_long")) && sizeof(query("new_long")) > 0)
  {
    set("long", query("new_long") + "\n");
  }
  else
  {
    set("long", query("long"));
  }
  // 设置新的wear_msg描述
  // 要对兵器进行判断，query(skill_type)为兵器，用wield_msg
  //                   query(armor_type)为防具，用wear_msg
  if (stringp(query("new_wear_msg")) && sizeof(query("new_wear_msg")) > 0)
  {
    if (stringp(query("skill_type")))
    {
      set("wield_msg", query("new_wear_msg") + "\n");
    }
    else
    {
      set("wear_msg", query("new_wear_msg") + "\n");
    }
  }
  else
  {
    if (query("skill_type"))
    {
      set("wield_msg", query("wield_msg") + "\n");
    }
    else
    {
      set("wear_msg", query("wear_msg") + "\n");
    }

  }

  // 设置新的remove_msg描述
  // 要对兵器进行判断，query(skill_type)为兵器，用wield_msg
  //                   query(armor_type)为防具，用wear_msg
  if (stringp(query("new_remove_msg")) && sizeof(query("new_remove_msg")) > 0)
  {
    if (query("skill_type"))
    {
      set("unwield_msg", query("new_remove_msg") + "\n");
    }
    else
    {
      set("remove_msg", query("new_remove_msg") + "\n");
    }

  }
  else
  {
    if (query("skill_type"))
    {
      set("unwield_msg", query("unwield_msg") + "\n");
    }
    else
    {
      set("remove_msg", query("remove_msg") + "\n");
    }
  }

*/
  if (query("enchase_all") >= 11)
  {
    log_file("srb_bug", base_name(this_object()) + "\n");
  }

  if (! MEMBER_D->is_valib_member(item_owner()) && query("enchase_all") > 4 )
  {
    set("enchase_all_last", query("enchase_all"));
    set("enchase_all", 4);
  }
  if (MEMBER_D->is_valib_member(item_owner()))
  {
    if (query("enchase_all_last") > query("enchase_all"))
      set("enchase_all", query("enchase_all_last"));
  }

        return r;
}

// 保存数据
int save()
{
  int res;

        if (base_name(this_object()) + ".c" == __FILE__)
                return 0;

  return ::save();
}

// 9/10级兵器攻击对手
mixed weapon_hit_ob(object me, object victim, int damage_bonus)
{
        int ap;
        int dp;
        int damage;

        if (attack_lvl < MAX_LEVEL ||
      query("owner/" + me->query("id")) < MAX_LEVEL * 80)
                return;

        if (attack_lvl >= ULTRA_LEVEL &&
            mapp(query("magic")))
        {
                return ITEM_D->weapon10lv_hit_ob(me, victim, this_object(), damage_bonus);
        }

        return ITEM_D->weapon_hit_ob(me, victim, this_object(), damage_bonus);
}

// 以下的函数因为执行的频度并不高，而且具有高度重复的性质，
// 所以都调用ITEM_D中的执行程序。

// 杀了人以后的奖励
void killer_reward(object me, object victim)
{
  ITEM_D->killer_reward(me, victim, this_object());
}

// 呼唤物品
int receive_summon(object me)
{
  return ITEM_D->receive_summon(me, this_object());
}

// 隐藏物品
int hide_anywhere(object me)
{
        return ITEM_D->hide_anywhere(me, this_object());
}

// 追寻物品
int receive_miss(object me)
{
        if (! is_weapon() && ! is_unarmed_weapon())
        {
                write("你无法追寻" + name() + "。\n");
                return 0;
        }

        if (attack_lvl < ULTRA_LEVEL)
        {
                write(name() + "尚未通灵，你难以自如的感应。\n");
                return 0;
        }

  return ITEM_D->receive_miss(me, this_object());
}

// 插在地上
int do_stab(object me)
{
        return ITEM_D->do_stab(me, this_object());
}

// 特殊能力
int do_touch(object me)
{
        if (attack_lvl != ULTRA_LEVEL)
                return notify_fail("你摸了半天，好像没什么反应。\n");

        return ITEM_D->do_touch(me, this_object());
}

// 圣化
int do_san(object me)
{
        if ((is_weapon() || is_unarmed_weapon()) &&
            attack_lvl < MAX_LEVEL)
                return notify_fail("你的武器等级不到，无法圣化。\n");

        return ITEM_D->do_san(me, this_object());
}

// 浸透物品
int do_imbue(object me, object imbue)
{
        return ITEM_D->do_imbue(me, this_object(), imbue);
}

// 镶嵌物品
int do_enchase(object me, object tessera)
{
        return ITEM_D->do_enchase(me, this_object(), tessera);
}

int query_autoload() { return (query("equipped") ? query("equipped") : "kept"); }

void autoload(string parameter)
{
    if (this_object()->query("enchase_all") >= 10)
    {
      log_file("srb_bug", base_name(this_object()) + "\n");
    }

        switch (parameter)
        {
        case "worn":
                this_object()->wear();
                break;

        case "wielded":
                this_object()->wield();
                break;
        }
}
