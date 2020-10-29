// Last Modified by sir on 4.10.2002
// 要开发某个城市，必须圣旨任命官职。官吏
// 除了知府外，别的副官只能开发某部分指数。
// 可以任命一些巡抚，专门来挑刺。降低指数。
// 自然灾害，破坏城市指数。
// topten定期朝廷来个评价。
// title激励玩家。
// city : 综合评价    city_level  巨型都市   大型都市  中型都市  小型都市
//         人口       people       800万      500万    300万     100万
//                   五项指数最大   8000       5000     3000      1000
//         农业       farming     力量 + 耐力   增加人口 减低民忠
//         治安       peace       身法 + 胆识   增加民忠
//         水利       water       根骨 + 定力   增加民忠
//         商业       business    福缘 + 容貌   增加人口 减低民忠
//         技术       technology  悟性 + 灵性   增加开发速度
//         税率       tax_rate    0-100 之间
//                    0-15  之间   非常满意 增加人口 增加民忠
//                    15-30 之间    满意    增加人口 民忠不变
//                    30-40 之间   微有怨言 人口不变  减低民忠 农业,治安受到破坏
//                    40-60 之间   怨声载道  人口减少 减低民忠 农业,治安,商业受到破坏
//                    60-80 之间   民怨沸腾  人口大减 民忠狂降 五项指数都受到破坏
//                    80-100之间   流民四起  人心不古 五项指数都狂减
//         民忠       fealty      0-100之间
//    容貌 per  力量 str 身法 dex 福缘 kar 耐力 sta
//    悟性 int  胆识 cor 定力 cps 根骨 con 灵性 spi

#ifndef CITYDATA
#define CITYDATA "/data/city/"  //文件存放地址
#endif
#define NAMEOFCITY "yangzhou"  //要开发的城市名
#define CNAMEOFCITY "扬州"     //中文城市名
#define FILE_PATH CITYDATA + NAMEOFCITY
#define LEVEL_OF_CITY "大型都市"  //综合评价
#define LEVEL 500   //城市的起始规模
#define MAX_LEVEL 800  //城市的最大规模

#include <ansi.h>
inherit ITEM;
inherit F_SAVE;

int do_kaifa(string);

void create()
{        set_name(HIY"官府通告"NOR, ({ "guanfu tonggao", "tonggao"}) );
        set("long","这是一张记录"+CNAMEOFCITY+"开发情况的官府通告。\n
想查看目前的情况，请先 help ms_city 了解具体操作。\n");
        set("LAST_KAIFA_PLAYER","none of us"); //最后开发过城市的玩家
        set("city_name", NAMEOFCITY); //城市名
        set("city_level", LEVEL_OF_CITY);// 综合评价
        set("fealty", LEVEL/10);  // 民忠
        set("tax_rate",LEVEL/10); // 税率
        set("people", LEVEL*10000);        // 人口
        set("water", LEVEL*10); // 水利
        set("water_pro", LEVEL*2); // 水利熟练度
        set("peace", LEVEL*10);  // 治安
        set("peace_pro", LEVEL*2);
        set("farming", LEVEL*10); // 城防
        set("farming_pro", LEVEL*2);
        set("business", LEVEL*10); // 商业
        set("business_pro", LEVEL*2);
        set("technology", LEVEL*10); // 技术
        set("technology_pro", LEVEL*2);
        set("no_get", 1);
        set("unit", "张");
        restore();
}



string query_save_file()
{
        return FILE_PATH;
}


void init()
{
        add_action("do_kaifa", "kaifa");
        add_action("do_chakan","chakan");
        add_action("do_tax","tax");
}
//int do_chakan()
string long()
{

        string msg;
        object ob;
        ob=this_object();
        msg=HIC"这个一张官府通告上面介绍了本城的开发情况: \n"+
        HIY"--------------------------------------------------------------------------\n"NOR;
        msg+=sprintf(HIC"\n 城市:" HIY "%8s" NOR HIC"\t\t城市规模: " HIY "%8s\n" NOR,
        CNAMEOFCITY,query("city_level", ob),);
        msg+=sprintf(HIC"\n 税率:  " HIW "%5d" NOR HIC"\t\t城中人口: " HIG "%8d\n" NOR,
        query("tax_rate", ob),query("people", ob),);
        msg+=sprintf(HIC"\n 治安: " HIW "%8d" NOR HIC"\t\t治安指数: " HIG "%8d\n" NOR,
        query("peace", ob),query("peace_pro", ob),);
        msg+=sprintf(HIC"\n 商业: " HIW "%8d" NOR HIC"\t\t商业指数: " HIG "%8d\n" NOR,
        query("business", ob),query("business_pro", ob),);
        msg+=sprintf(HIC"\n 农业: " HIW "%8d" NOR HIC"\t\t农业指数: " HIG "%8d\n" NOR,
        query("farming", ob),query("farming_pro", ob),);
        msg+=sprintf(HIC"\n 水利: " HIW "%8d" NOR HIC"\t\t水利指数: " HIG "%8d\n" NOR,
        query("water", ob),query("water_pro", ob),);
        msg+=sprintf(HIC"\n 技术: " HIW "%8d" NOR HIC"\t\t技术指数: " HIG "%8d\n" NOR,
        query("technology", ob),query("technology_pro", ob),);
        msg+=HIY"--------------------------------------------------------------------------\n"NOR;
        return msg;
}

int do_kaifa(string arg)
{

        object ob = this_object();
        object me = this_player();
        string msg;
        int pro_num, lvl_num,add_num,me_score,me_balance;
        int ob_people,ob_taxrate,ob_technology,ob_fealty;
//        kaifa,money,i;

        me_score=query("score", me);
        me_balance=query("balance", me);
        ob_people=query("people", ob);
        ob_taxrate=query("tax_rate", ob);
        ob_technology=query("technology", ob)/100;
/*
        if( !query("CITY_KAIFA", me)) )
                return notify_fail("你没有得到康亲王的许可，无法协助开发朝廷所属地盘。\n");
        if( query("CITY_KAIFA/name", me) != query("city_name", ob) )
                return notify_fail("你要协助开发的城市好象不是这里吧？\n");
*/
//江湖阅历小于1000就不让继续开发

        if (me_score<1000)
                return notify_fail("你的江湖阅历不够，还是多积累点阅历再来吧!\n");
//存款小于100 gold 就不让继续开发
        if(me_balance<1000000)
                return notify_fail("你的存款不够，无法满足开发所需要的资金要求!\n");
        if( query_temp("busy", ob) )
                return notify_fail("有人刚下过开发命令，稍候........\n");
        if( !arg || ( arg!= "水利" && arg!="农业"
                  && arg!="治安" && arg!="商业" && arg!="技术"))
                return notify_fail("你要开发什么？\n");
//   商业 business    福缘 + 容貌 + 本城技术值  增加人口 减低民忠
        if( arg=="商业")
           {
              tell_object(me,"你思虑再三，决定开始协助官府开发"+CNAMEOFCITY+"的商业，请等候结果吧！\n");
              pro_num=query("business_pro", ob);
              lvl_num=query("business", ob);
              if(lvl_num >= MAX_LEVEL*10)
                {
                 return notify_fail(CNAMEOFCITY+"的商业已经足够发达了，你可以试着去开发其他项目了！\n");
                }
              else
              {
                      add_num=query("per", me)+query("kar", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"【风闻】"HIG+CNAMEOFCITY+"的商业在"+query("name", me)+"的协助开发下变的越来越繁华了！\n"NOR,users());
                     ob_people=ob_people+lvl_num*(1+random(3));
                     if(ob_fealty>=5) ob_fealty-=random(5);
                     }
//                 ob->set("people",ob_people);
//                 ob->set("fealty",ob_fealty);
                 set("business_pro", pro_num, ob);
                 set("business", lvl_num, ob);
                 message_vision( HIW"城市的商业指数提高了。\n"NOR,me);
                }
           }
//    农业       farming     力量 + 耐力+ 本城技术值   增加人口 减低民忠
        if( arg=="农业")
           {
              tell_object(me,"你思虑再三，决定开始协助官府开发"+CNAMEOFCITY+"的农业，请等候结果吧！\n");
              pro_num=query("farming_pro", ob);
              lvl_num=query("farming", ob);
              if(lvl_num >= MAX_LEVEL*10)
                {
                 return notify_fail(CNAMEOFCITY+"的农业已经足够发达了，你可以试着去开发其他项目了！\n");
                }
              else
              {
                      add_num=query("str", me)+query("sta", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"【风闻】"HIG+CNAMEOFCITY+"的农田在"+query("name", me)+"的协助开垦下变的越来越肥沃了！\n"NOR,users());
                     ob_people=ob_people+lvl_num*(1+random(3));
                     if(ob_fealty>=5) ob_fealty-=random(5);;
                     }
//                 ob->set("people",ob_people);
//                 ob->set("fealty",ob_fealty);
                 set("farming_pro", pro_num, ob);
                 set("farming", lvl_num, ob);
                 message_vision( HIY"城市的农业指数提高了。\n"NOR,me);
                }
           }
//   治安   peace   身法 + 胆识+ 本城技术值   增加民忠
        if( arg=="治安")
           {
              tell_object(me,"你思虑再三，决定开始协助官府开发"+CNAMEOFCITY+"的治安，请等候结果吧！\n");
              pro_num=query("peace_pro", ob);
              lvl_num=query("peace", ob);
              if(lvl_num >= MAX_LEVEL*10)
                {
                 return notify_fail(CNAMEOFCITY+"的治安已经足够发达了，你可以试着去开发其他项目了！\n");
                }
              else
              {
                      add_num=query("dex", me)+query("cor", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"【风闻】"HIG+CNAMEOFCITY+"的治安在"+query("name", me)+"的协助治理下变的越来越安定了！\n"NOR,users());
                     if(ob_fealty<100) ob_fealty+=random(5);
                     if(ob_fealty>100) ob_fealty=100;
                     }
//                 ob->set("fealty",ob_fealty);
                 set("peace_pro", pro_num, ob);
                 set("peace", lvl_num, ob);
                 message_vision( HIC"城市的治安指数提高了。\n"NOR,me);
                }
           }
//    水利  water       根骨 + 定力+ 本城技术值   增加民忠
        if( arg=="水利")
           {
              tell_object(me,"你思虑再三，决定开始协助官府开发"+CNAMEOFCITY+"的水利，请等候结果吧！\n");
              pro_num=query("water_pro", ob);
              lvl_num=query("water", ob);
              if(lvl_num >= MAX_LEVEL*10)
                {
                 return notify_fail(CNAMEOFCITY+"的水利已经足够发达了，你可以试着去开发其他项目了！\n");
                }
              else
              {
                      add_num=query("con", me)+query("cps", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"【风闻】"HIG+CNAMEOFCITY+"的水利在"+query("name", me)+"的协助开发下变的越来越发达了！\n"NOR,users());
                     if(ob_fealty<100) ob_fealty+=random(5);
                     if(ob_fealty>100) ob_fealty=100;
                     }
//                 ob->set("fealty",ob_fealty);
                 set("water_pro", pro_num, ob);
                 set("water", lvl_num, ob);
                 message_vision( HIC"城市的水利指数提高了。\n"NOR,me);
                }
           }
//  技术   technology  悟性 + 灵性   增加开发速度
        if( arg=="技术")
           {
              tell_object(me,"你思虑再三，决定开始协助官府开发"+CNAMEOFCITY+"的技术，请等候结果吧！\n");
              pro_num=query("technology_pro", ob);
              lvl_num=query("technology", ob);
              if(lvl_num >= MAX_LEVEL*10)
                {
                 return notify_fail(CNAMEOFCITY+"的技术已经足够发达了，你可以试着去开发其他项目了！\n");
                }
              else
              {
                      add_num=query("int", me)+query("spi", me);
                add_num = add_num + random(ob_technology);
                pro_num=pro_num+add_num;
                if (pro_num>=lvl_num)
                    {
                     lvl_num+=1;
                     pro_num = pro_num - lvl_num;
                     message("channel:sys",HIY"【风闻】"HIG+CNAMEOFCITY+"的技术在"+query("name", me)+"的协助研究下变的越来越先进了！\n"NOR,users());
                     }
                 set("technology_pro", pro_num, ob);
                 set("technology", lvl_num, ob);
                 message_vision( HIB"城市的技术指数提高了。\n"NOR,me);

                }
           }
//每次执行开发指令，都要考虑到城市税率对本轮开发的影响 这样感觉才有点动态性 呵呵
//         0-15  之间   非常满意 增加人口 增加民忠
//         15-30 之间    满意    增加人口 民忠不变
//      30-40 之间   微有怨言 人口不变  减低民忠 农业,治安受到破坏
//      40-60 之间   怨声载道  人口减少 减低民忠 农业,治安,商业受到破坏
//      60-80 之间   民怨沸腾  人口大减 民忠狂降 五项指数都受到破坏
//      80-100之间   流民四起  人心不古 五项指数都狂减
       if( ob_taxrate>=0&&ob_taxrate<=15)
           {
             if(ob_fealty<100) ob_fealty+=random(5);
             if(ob_fealty>100) ob_fealty=100;
             if(ob_people<MAX_LEVEL*10000)
             ob_people=ob_people+(100-ob_taxrate)*(10+random(5));
             message_vision( MAG"由于城市的税率定的相当低，这里百姓非常满意，并有很多外地的人口来这里谋生。\n"NOR,me);
            }

       else if( ob_taxrate>=16&&ob_taxrate<=30)
            {
             if(ob_people<MAX_LEVEL*10000)
             ob_people=ob_people+(100-ob_taxrate)*(10+random(5));
             message_vision( GRN"由于城市的税率定的相对较低，百姓还算满意，经常有一些外地的人口来这里谋生。\n"NOR,me);
             }

       else if( ob_taxrate>=31&&ob_taxrate<=40)
             {
               if(ob_fealty>=5) ob_fealty-=random(5);
               pro_num=query("farming_pro", ob);
               lvl_num=query("farming", ob);
               if (pro_num > 100)
                   {
                      pro_num = (int)pro_num-random(100);
                      set("farming_pro", pro_num, ob);
                    }
               pro_num=query("peace_pro", ob);
               if (pro_num > 100)
                   {
                      pro_num = (int)pro_num-random(100);
                      set("peace_pro", pro_num, ob);
                    }
               message_vision( CYN"城中的一些人认为官府的税率定的不太合理，微有怨言，有人在城里发现小偷和一些不愿种田的农民。\n"NOR,me);
               }
        else if( ob_taxrate>=41&&ob_taxrate<=60)
             {
                     if(ob_fealty>=5) ob_fealty-=random(5);
                     ob_people=ob_people-ob_taxrate*(10+random(3));
                     pro_num=query("farming_pro", ob);
                     if (pro_num > 100)
                   {
                      pro_num = (int)pro_num-random(100);
                      set("farming_pro", pro_num, ob);
                    }
                 pro_num=query("peace_pro", ob);
                 if (pro_num > 100)
                    {
                      pro_num = (int)pro_num-random(100);
                      set("peace_pro", pro_num, ob);
                     }
                 pro_num=query("business_pro", ob);
                 if (pro_num > 100)
                     {
                      pro_num = (int)pro_num-random(100);
                      set("business_pro", pro_num, ob);
                     }
                     message_vision( YEL"城中百姓怨声载道，大部分商人也认为官府收的税太高了，有人在城中搞起小破坏，来抱怨对官府的不满。\n"NOR,me);
                     }
         else if( ob_taxrate>=61&&ob_taxrate<=80)
             {
                     if(ob_fealty>=5) ob_fealty-=random(5);
                     ob_people=ob_people-ob_taxrate*(10+random(6));
                     if( query("farming", ob)>5 && random(2) == 1 )
                          addn("farming", -1, ob);
                if( query("water", ob)>5 && random(2) == 1 )
                          addn("water", -1, ob);
                     if( query("business", ob)>5 && random(2) == 1 )
                          addn("business", -1, ob);
                     if( query("technology", ob)>5 && random(2) == 1 )
                          addn("technology", -1, ob);
                     if( query("peace", ob)>5 && random(2) == 1 )
                          addn("peace", -1, ob);
                     message_vision( BLU"城中民怨沸腾，百姓一致认为官府收的税太高了，并逐渐对这里的地方官员失去信心。\n"NOR,me);
             }
        else
             {
                     if(ob_fealty>=5) ob_fealty-=random(5);
                     ob_people=ob_people-ob_taxrate*(10+random(9));
                     if( query("farming", ob)>5 && random(2) == 1 )
                          addn("farming", -2, ob);
                if( query("water", ob)>5 && random(2) == 1 )
                          addn("water", -2, ob);
                     if( query("business", ob)>5 && random(2) == 1 )
                          addn("business", -2, ob);
                     if( query("technology", ob)>5 && random(2) == 1 )
                          addn("technology", -2, ob);
                     if( query("peace", ob)>5 && random(2) == 1 )
                          addn("peace", -2, ob);
                     message_vision( RED"苛政猛于虎，城中百姓无法忍受官府的盘剥，纷纷背井离乡。\n"NOR,me);
                     }
// 每次执行指令消耗50的江湖阅历 和一定的存款（与本城的税率有关 如果税率达100就不花钱）
        me_score = me_score-50;
        me_balance = me_balance-2000*(100-ob_taxrate);
        set("score", me_score, me);
        set("balance", me_balance, me);
//防止执行过程中出现负人口 和民忠值超过范围
        if( ob_people<0) ob_people=1;
        set("people", ob_people, ob);
        if (ob_fealty<0) ob_fealty=0;
        if (ob_fealty>100) ob_fealty=100;
        set("fealty", ob_fealty, ob);
        save();
        set_temp("busy", 1, ob);
        remove_call_out("enough_rest");
//1秒后取消busy
        call_out("enough_rest", 1);
        return 1;
}
int do_tax(string arg)
{  int ob_taxrate,taxrate;
   object ob=this_object();
   if( query_temp("busy", ob) )
        return notify_fail("有人刚下过开发命令，稍候........\n");
   if( !arg
        ||      !sscanf(arg, "%d", taxrate) )
      return notify_fail("你想将税率定为多少？\n");
   if(taxrate>100||taxrate<0)
      return notify_fail("税率只能在0到100之间！\n");
   ob_taxrate=taxrate;
   set("tax_rate", ob_taxrate, ob);
   save();
   set_temp("busy", 1, ob);
   remove_call_out("enough_rest");
//1秒后取消busy
   call_out("enough_rest", 1);
   return 1;
}

void enough_rest()
{
        delete_temp("busy");
}
