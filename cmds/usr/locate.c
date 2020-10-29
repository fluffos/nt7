 // by Tie@fy3
 
#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_DBASE;

#define MAX_DIS 7
#define MAX_ALT  2
#define MAX_DIR  8  
#define MYSQL_SCHEDULE_D    "/adm/daemons/mysql_schedule_d"

mapping *quests;
string locate_obj(object me, string strr);
object find_env(object ob);

string *output = ({
" B"+
" B"+
" B"+
" B"+
" B"+
" B"+
" B"+
" B"+
" B"+
" B",
"B"+
"B"+
"B"+
"B"+
"B"+
"B"+
"B"+
"B"+
"B"+
"B"
});


string *c_num= ({
"      ;'       B"+
" , ''';;'''' , B"+
",;';;';;';;';;'B"+
";' ,, ;; ,, ;' B"+
"    ,;',';,,   B"+
",,'',,,;;,,;';'B"+
"         ;'    B"+
"     ',,;'     B"+
"       ';'     B"+
"               B",
"               B"+
"               B"+
"               B"+
"               B"+
"               B"+
",,,,,,,,,,,;,  B"+
"               B"+
"               B"+
"               B"+
"               B",
"               B"+
"               B"+
"               B"+
"  ,,,,,,,,,;,  B"+
"               B"+
"             , B"+
"'''''''''''''''B"+
"               B"+
"               B"+
"               B",
"           ,   B"+
"  '''''''''''  B"+
"               B"+
"  ,,,,,,,,,;,  B"+
"               B"+
"             , B"+
"'''''''''''''''B"+
"               B"+
"               B"+
"               B",
",            , B"+
";;'';;'';;'';;'B"+
";;  ;;  ;;  ;; B"+
";;  ;;  ;;  ;; B"+
";; ;;   ;;,,;; B"+
";;,'     ''';; B"+
";;'''''''''';; B"+
"'           '  B"+
"               B"+
"               B",
" ,,,,,,,,,,,;, B"+
"     ;;        B"+
"     ;;   ,    B"+
" '''';;'';;'   B"+
"     ;;  ;;    B"+
"    ;;   ;;    B"+
"    ;;   ;;  , B"+
"'''''''''''''''B"+
"               B"+
"               B",
"     ',,       B"+
"      ';;      B"+
",,,,,,,;,,,,,;,B"+
"     ,  ,      B"+
"    ;;'  ;,    B"+
"   ,;'    ;,   B"+
"  ,;'      ;;  B"+
" ,'         ;' B"+
"               B"+
"               B",
"      ,        B"+
"      ;;       B"+
"      ;;     , B"+
"    ,,;;,,'''''B"+
"''''  ;;       B"+
"      ;;     , B"+
"      ;;,,,,,;,B"+
"       ''''''' B"+
"               B"+
"               B",
"    ,   ;,     B"+
"    ;;  ;;     B"+
"    ;;  ;;     B"+
"    ;;  ;;     B"+
"   ,;'   ;;    B"+
"  ,;'    ';,   B"+
" ,;'      ';;, B"+
",'          ';'B"+
"               B"+
"               B",
"     ;,        B"+
"     ;;   ,    B"+
" '''';;'';;'   B"+
"     ;;  ;;    B"+
"    ,;'  ;;    B"+
"   ,;'   ;;    B"+
"  ,;'    ;;  ; B"+
",''      ';;;;'B"+
"               B"+
"               B",
"      ;,       B"+
"      ;;       B"+
"      ;;       B"+
"'''''';;'''''' B"+
"      ;;       B"+
"      ;;       B"+
"      ;;       B"+
"      ;'       B"+
"               B"+
"               B"
});

string addcolor(string outstring)
{
        switch(random(10)) {
        case 0: outstring += RED; break;
        case 1: outstring += HIR; break;
        case 2: outstring += GRN; break;
        case 3: outstring += HIG; break;
        case 4: outstring += YEL; break;
        case 5: outstring += HIY; break;
        case 6: outstring += BLU; break;
        case 7: outstring += HIB; break;
        case 8: outstring += HIM; break;
        case 9: outstring += HIC; break;
        }

	return outstring;
}


mixed my_number()
{
 string outstring;
 int out;
 int orinum;
 int num = random(100000000);
 mixed alle;
 string *out8,*out7,*out6,*out5,*out4,*out3,*out2,*out1;
	orinum = num;
	switch(random(10)) {
	case 0: outstring = RED"\n"; break;
        case 1: outstring = HIR"\n"; break;
        case 2: outstring = GRN"\n"; break;
        case 3: outstring = HIG"\n"; break;
        case 4: outstring = YEL"\n"; break;
        case 5: outstring = HIY"\n"; break;
        case 6: outstring = BLU"\n"; break;
        case 7: outstring = HIB"\n"; break;
        case 8: outstring = HIM"\n"; break;
        case 9: outstring = HIC"\n"; break;
	}
	if(num>99999999) num =99999999;
	if(num >= 10000000) 
	{
	out = num/10000000;
	out8 = explode(c_num[out],"B");
	num = num%10000000;
	}
	else
	if(orinum > num)	
	out8 = explode(c_num[0],"B");
	else
	out8 = explode(output[0],"B");

        if(num >= 1000000) 
        {
        out = num/1000000;
        out7 = explode(c_num[out],"B");
        num = num%1000000;
        }
        else
        if(orinum > num)
        out7 = explode(c_num[0],"B");
        else
        out7 = explode(output[0],"B");


        if(num >= 100000) 
        {
        out = num/100000;
        out6= explode(c_num[out],"B");
        num = num%100000;
        }
        else
        if(orinum > num)
        out6 = explode(c_num[0],"B");
        else
        out6 = explode(output[0],"B");

        if(num >= 10000) 
        {
        out = num/10000;
        out5 = explode(c_num[out],"B");
        num = num%10000;
        }
        else
        if(orinum > num)
        out5 = explode(c_num[0],"B");
        else
        out5 = explode(output[0],"B");


        if(num >= 1000) 
        {
        out = num/1000;
        out4 = explode(c_num[out],"B");
        num = num%1000;
        }
        else
        if(orinum > num)
        out4 = explode(c_num[0],"B");
        else
        out4 = explode(output[0],"B");

        if(num >= 100) 
        {
        out = num/100;
        out3 = explode(c_num[out],"B");
        num = num%100;
        }
        else
        if(orinum > num)
        out3 = explode(c_num[0],"B");
        else
        out3 = explode(output[0],"B");


        if(num >= 10) 
        {
        out = num/10;
        out2 = explode(c_num[out],"B");
        num = num%10;
        }
        else
        if(orinum > num)
        out2 = explode(c_num[0],"B");
        else
        out2 = explode(output[0],"B");

        out1 = explode(c_num[num],"B");

	for(out=0;out<sizeof(out8);out++)
		outstring += addcolor(out8[out])+"  "+addcolor(out7[out])+"  "+
				addcolor(out6[out])+"  "+addcolor(out5[out])+"\n";
	outstring += "\n";
        for(out=0;out<sizeof(out4);out++)
                outstring += addcolor(out4[out])+"  "+addcolor(out3[out])+"  "+
			addcolor(out2[out])+"  "+addcolor(out1[out])+"\n";
    
	alle = ({ outstring + NOR, orinum });
				

return alle;


}





int main(object me, string str)
{
        string output = "";
        string id, code;
        object room;
        int    x0, y0, z0;
        mixed alle;
        
        room = environment(me);
        x0=query("coor/x", room);
        y0=query("coor/y", room);
        z0=query("coor/z", room);
   
        if( !x0 && !y0 && !z0 && base_name(room) != "/d/city/guangchang" ) 
                return notify_fail(WHT "这个地方不能使用locate指令，只有在有task发布的地区才可以使用！\n" NOR);

        if( !wizardp(me) && time() - query_temp("last_locate", me) < 1 )
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");  
                
        if( !str ) 
                return notify_fail("指令格式: locate <物品>\n");

        if( query("qi", me)<30 )
                return notify_fail("你的气不足以查寻位置。\n");
                
        set_temp("last_locate", time(), me);
        if( sscanf(str, "answer %s", str) == 1 && sizeof(str) > 0 )
        {
                if( str == "giveup" )
                {
                        if( query("balance", me) < 5000000 )
                                return notify_fail("你的存款不足500两黄金，无法取消本次验证码。\n");
                        
                        addn("balance", -5000000, me);
                     //   MYSQL_SCHEDULE_D->delete_captcha(me->query_id(1));
                        delete_temp("task_captcha_code", me);
                        delete_temp("task_captcha_str", me);
                        delete_temp("task_captcha_time", me);
                        write("本次验证码取消成功。\n");
                        return 1;
                }
                if( str == query_temp("task_captcha_code", me) )
                {
                     //   MYSQL_SCHEDULE_D->delete_captcha(me->query_id(1));
                        delete_temp("task_captcha_code", me);
                        str = query_temp("task_captcha_str", me);
                        delete_temp("task_captcha_str", me);
                        me->receive_damage("qi", 20);
                        output = TASK_D->locate_ob(me, str);
                        if( output == "" )
                                return notify_fail("确定不了" + str + "的大概位置。\n");
                        
                        write(output);
                        return 1;
                }
                else
                        return notify_fail("验证码输入错误。\n");
        }

        if( query_temp("task_captcha_code", me) )
        {
                write("\n输入「locate answer 验证码」以获得物品位置。\n"NOR);
                return 1;
           //     write(HIY"\n请至以下网页输入你的ID，取得"+pnoun(2, me)+"的验证码：\n\n"NOR"http://www.muds.cn/php/test.html\n\n取得验证码后输入「locate answer 验证码」以获得物品位置。\n"NOR);
                return 1;
        }

        if( time() - query_temp("task_captcha_time", me) > 300 )
        {
                int r;
                
                r = random(100);
                if( r < 10 )
                {
                        id = me->query_id(1);
                       // if( random(2) ) code = sprintf("%d%d%d%d%d", random(10), random(10), random(10), random(10), random(10)); else
                       // code = sprintf("%c%c%c%c%c", range_random(97,122), range_random(97,122), range_random(97,122), range_random(97,122), range_random(97,122));
                     //   MYSQL_SCHEDULE_D->set_captcha(id, code);
                     alle=my_number();
                     
  set_temp("task_captcha_code", sprintf("%d",alle[1]), me);
                        set_temp("task_captcha_str", str, me);
                        set_temp("task_captcha_time", time(), me);
                        write(alle[0]);
			   write("\n请输入以上校验码：");
                    //    write(HIY"\n建立新的TASK验证码...请至以下网页输入你的ID，取得"+pnoun(2, me)+"的验证码：\n\n"NOR"http://www.muds.cn/php/test.html\n\n取得验证码后输入「locate answer 验证码」以获得物品位置。\n"NOR);
                        return 1;
                }
                else if( r < 20 )
                {
                        mapping question;
                
                        question = X_PointD->get_question();
                        code = question["answer"];
                        set_temp("task_captcha_code", code, me);
                        set_temp("task_captcha_str", str, me);
                        set_temp("task_captcha_time", time(), me);
                        write("\n验证码为：\n\n"NOR);
                        write(question["question"]);
                        write("\n输入「locate answer 验证码」以获得物品位置。\n"NOR);
                        return 1;
                }
        }
                
        me->receive_damage("qi", 20);
        output = TASK_D->locate_ob(me, str);
        // if(output=="")
        // output = QUESTNPC_D->locate_obj(me, str);
        
        if( output == "" )
                return notify_fail("确定不了" + str + "的大概位置。\n");
        
        write(output);
        return 1;
}  

object find_env(object ob)
{
        while(ob)
        {
                if( query("coor", ob) )
                        return ob;
                else 
                        ob = environment(ob);        
        }
        return ob;
}        

int help(object me)
{
        write(@HELP
指令格式: locate <物品> 
这个指令是用来得知使命物品的大概位置。
朝廷官员还可以用此指令查寻人物的大概位置。 
HELP
        );
        return 1;
} 
