// Modified by lonely@NT
int zuji_times; 
void zuji_begin(int num)
{
     object killer;
     object killer1;
     int n;

/*
     if( zuji_times < 1 )
     {
        remove_call_out("zuji_begin");
        return;
     }
*/

     if( zuji_times >= 8  )
     {
        remove_call_out("zuji_begin");
        remove_call_out("zuji_new");
        call_out("zuji_new",60,num);
        return;
     }

     zuji_times++;
        message("story", HIY "【武林传奇】" NOR + WHT +
                         (random(2) ? "只听得的的马蹄之声，一队契丹武士手执长矛"
                                    : "只见一队契丹武士挥舞着长矛，指指点点，") +
                         "来到了雁门关外。\n" + NOR, listeners);
     message("channel:rumor", MAG"【故事传闻】只听得的的马蹄之声，一队契丹武士挥舞着长矛，身背弓箭，指指点点，来到了雁门关外。\n"
        "带头大哥道：虽然这些契丹人看似来狩猎的，但不能马虎，一个也留不得！\n"
        "众人的暗器便射了出去，钢镖、袖箭、飞刀、铁锥……每件都喂了剧毒。\n"
        "只听得众辽人啊啊呼叫，乱成一团，一大半都摔下马来。\n"
        "众人一拥而上。刀剑齐施！\n"NOR,users());
     for(n=0;n<num;n++)
     {
          killer=new("/quest/zuji/qidanb");
          killer->move("/d/yanmen/road");
          killer->change_ob();
/*
          killer1=new("/quest/zuji/songb");
          killer1->move("/d/yanmen/shance");
          killer1->change_ob();
*/
     }

     remove_call_out("zuji_begin");
     call_out("zuji_begin",30,num);
     return;
}
              
void zuji_new(int num) 
{
     object killer;
     int n;
/*
     if( zuji_times >= 4 )
     {
*/
          zuji_times=1;
   message("channel:rumor",MAG"【故事传闻】雁门关外，只见这时，马蹄声又响起来，辽人当先的马匹奔近。\n"
       "只见这些契丹武士身上都披皮裘，或拿长矛，或提弯刀，或弯弓搭箭，或停猎鹰，高歌而来。\n"
       "带头大哥一声长啸，就是他们了！众人的暗器便射了出去，钢镖、袖箭、飞刀、铁锥……每件都喂了剧毒。\n"
       "只听得众辽人啊啊呼叫，乱成一团，一大半都摔下马来。\n"
       "众人一拥而上。刀剑齐施！\n"NOR,users());

     for(n=0;n<num;n++)
     {
          killer=new("/quest/zuji/qidanb");
          killer->move("/d/yanmen/road");
          killer->change_ob();
     }
          remove_call_out("zuji_continue");
          call_out("zuji_continue",60,num);
     return;
}


void zuji_continue(int num)
{
          message("channel:rumor", HIR"【故事传闻】经过一段时间的殊死"
            +HIR"搏斗，将这剩下几人尽数杀了，没一个活口逃走。！\n"NOR,users()); 
          remove_call_out("zuji_over");
          call_out("zuji_over",30,num);
}
void zuji_over(int num)
{
     object killer,killer1;
     int n;
   message("channel:rumor",MAG"【故事传闻】只听得马蹄声音，西北角又有两骑马驰来，马上是男女二人。\n"
        "这两人见到那一十九名武士死在地下，那男子立时神色十分凶猛，向众人大声喝问。\n"
        "辽人：$*@!@#$%^&*！\n"
        "铁塔方大雄举起一条镔铁棍，喝道：兀那辽狗，纳下命来！挥棍便向那契丹男子打了过去。\n"
        "那辽人右臂伸出，折断方大雄右臂关节，将他的身子挑了起来，连人带棍，一起摔在道旁。\n"
        "辽人：#$%^&*$*@!@！\n"
        "当下六七人一拥而上，向那辽人攻了过去。另外四五人则向那少妇攻击。\n"
        "那少妇被人一剑便斩断一条手臂，抱着的婴儿跌下地来，跟着便被一刀砍去了半边脑袋。\n"
        "只听得那辽人眼睛登时红了，脸上神色可怖之极，暴喝一声，冲向敌阵。\n"
        ".........\n"
        NOR+HIY"夕阳如血，雁关门外朔风呼号.........\n"NOR,users());
/*
     for(n=0;n<num;n++)
     {
          killer=new("/quest/zuji/qidanb");
          killer->move("/d/yanmen/road");
          killer->change_ob();
     }
*/
          killer1=new("/quest/zuji/xiao");
          killer1->move("/d/yanmen/road");
          killer1->change_ob();
     return;
}
void zuji_close()
{
   string temp;
   int killer_rate,chousha_count;
   object *ulist;
   int k;

   ulist=users();
   k=sizeof(ulist);
   while (k--)
   {
      if( !environment(ulist[k]) || !ulist[k]->query_temp("zuji")) continue;
      ulist[k]->delete_temp("zuji");
      ulist[k]->delte_temp("apply/short");
      ulist[k]->add("combat_exp",20000);
      ulist[k]->add("potential",5000);
      ulist[k]->add("weiwang",20);
           tell_object(ulist[k],HIW"你获得了"+HIR+chinese_number(20000) 
           +HIW"点经验和"+HIR+chinese_number(5000)+HIW"点潜能奖励和"+HIR+chinese_number(20)+HIW"点威望！！\n"NOR);   
   }

  message("channel:rumor",MAG"【故事传闻】只听得当的一声，那辽人掷下短刀，俯身抱起他妻子的尸身和儿子，走到崖边，\n"
       "涌身便往深谷中跳了下去。忽然间“哇哇”两声婴儿的啼哭，从乱石谷中传了上来，跟着黑黝黝一件物事从\n"
       "谷中飞上，拍的一声轻音，正好跌在汪帮主身上。婴儿啼哭之声一直不止，正是那个婴儿。\n"NOR,users());

   zuji_times=0;
   killer_rate=6;
   temp=sprintf("%d",killer_rate);
   write_file("/quest/chousha/killer_rate",temp,1);
   chousha_count=0;
   temp=sprintf("%d",chousha_count);
   write_file("/quest/chousha/chousha_count",temp,1);

   return;
}

void zuji_fail()
{
     remove_call_out("zuji_begin");
     remove_call_out("zuji_new");
     remove_call_out("zuji_continue");
     remove_call_out("zuji_over");
     remove_call_out("zuji_close");
     remove_call_out("remove_enemy");
     call_out("remove_enemy",1);
     return;
}
void remove_enemy()
{
   string temp;
        object *enemys;
        int i, chousha_count;
        mapping my = query_entire_dbase();

   chousha_count=0;
   temp=sprintf("%d",chousha_count);
   write_file("/quest/chousha/chousha_count",temp,1);
        if (arrayp(enemys = children("/quest/zuji/qidanb")))
        {
                for (i = 0; i < sizeof(enemys); i++)
                {
                        if (enemys[i]->is_fighting())
                        {
                                enemys[i]->remove_all_killer();
                                tell_room(environment(enemys[i]), HIW "只见" + enemys[i]->name()
                                        + "突然面色一变，迅速攻出几招，跳出战圈转身逃了。\n");
                        }
                        else {
                                tell_room(environment(enemys[i]), HIW "只见" + enemys[i]->name()
                                        + "掐值一算，突然脸色大变，急急忙忙地逃走了。\n");
                        }
                        destruct(enemys[i]);
                }
        }
        return; 
}
