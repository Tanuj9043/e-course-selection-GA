#include <bits/stdc++.h>
#include <cstring>
using namespace std;

#define FIO ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mp(x, y) make_pair(x, y)
#define set(p) memset(p, -1, sizeof(p))
#define clr(p) memset(p, 0, sizeof(p))
#define mem(p, v) memset(p, v, sizeof(p))
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define ll long long
#define ull unsigned long long
#define ld long double
#define vv(x) vector<x >
#define pb push_back
#define pob pop_back
#define pf push_front
#define pof  pop_front
#define umap(x,y) unordered_map<x,y >
#define pq priority_queue
#define pp(x) pair<x, x >
#define fori(i,n) for(int i=0; i<n; i++)
#define forl(i,n) for(ll i=0; i<n; i++)
#define tr(it,c) for(auto it=c.begin(); it!=c.end(); it++)
#define file freopen("inp.in","r",stdin); freopen("outp.out","w",stdout)

const double pi = acos(-1.0);
const int imax = 2147483647;
const int imin = -2147483647;
const ll lmax = 9223372036854775807;
const ll lmin = -9223372036854775807;

class course{
public:
    string name;

    ll interest, cost, time, teacher_expertise,
    rating, content_quality;

    course(){
        interest=cost=time=teacher_expertise=
        rating=content_quality=0;
    }

    void printCourse(){
        cout<<"============================="<<name<<"===============================\n";
        cout<<"Interest               : "<<interest<<"\n";
        cout<<"Cost                   : "<<cost<<"\n";
        cout<<"Time                   : "<<time<<" months\n";
        cout<<"Rating                 : "<<rating<<"\n";
        cout<<"Teacher's Expertise    : "<<teacher_expertise<<"\n";
        cout<<"Content                : "<<content_quality<<"\n";
        cout<<"==========================================================================\n\n\n";
    }
};

ll population = 1000;
ll courses = 40;

int main(){
    ofstream fa("graph.csv");
    fa<<"Generation,Fitmax,Fitness"<<endl;

	srand(time(NULL));

    pair<course,ll> p[population][courses];

    fori(j,courses){
        course c;

        c.name = "Course " + to_string(j+1);
        c.interest = rand()%10 + 1;
        c.cost = rand()%2501 + 500;
        c.time = rand()%2 + 1;
        c.teacher_expertise = rand()%10 + 1;
        c.rating = rand()%10 + 1;
        c.content_quality = rand()%10 + 1;

        //c.printCourse();

        fori(i,population){
            p[i][j].ss = rand()%2;
            p[i][j].ff = c;
        }
    }

	vector<pair<double,int> > v;
    vector<double> stop;
    double smx, smn;
    ll gen=0;
    while(1){
		v.clear();

        ///cout<<"==========================GENERATION "<<(gen+1)<<"===============================\n";

        double interest, rating, cost, time, fitness, fitmax=lmin, fitAvg, cnt;

        fori(i,population){
            interest = rating = cost = time = cnt = 0;

            fori(j,courses){
                if(p[i][j].ss==1){
					///printf("1 ");
                    interest += p[i][j].ff.interest;
                    rating += p[i][j].ff.rating;
                    cost += p[i][j].ff.cost;
                    time += p[i][j].ff.time;
                    cnt++;
                }
                ///else printf("0 ");
            }

            //CONSTRAINTS
            if(cnt==0 || cost>60000 || time>18){
                fitness=0.0;
                fitmax=max(fitmax,fitness);
                v.pb(mp(fitness,i));
                continue;
            }
            
            /*
			printf("Cost = %lf\nTime = %lf\n",cost,time);
			printf("Interest Factor : %lf\n",(0.4) * (interest/(cnt*10.0)));
			printf("Rating Factor   : %lf\n",(0.1) * (rating/(cnt*10.0)));
			printf("Cost Factor     : %lf\n",(0.3) * (60000.0/cost));
			printf("Time Factor     : %lf\n\n",(0.2) * (18.0/time));
            */

            fitness = 0.0;
            fitness += (0.4) * (interest/(cnt*10.0));
            fitness += (0.1) * (rating/(cnt*10.0));
            fitness += (0.3) * (60000.0/cost);
            fitness += (0.2) * (18.0/time);

			v.pb(mp(fitness,i));

            fitAvg+=fitness;
            fitmax=max(fitmax,fitness);
        }

		fitAvg/=(double)population;
        fa<<gen<<","<<fixed<<setprecision(5)<<fitmax<<","<<fixed<<setprecision(5)<<fitAvg<<endl;

        ///cout<<"======================================================================\n\n\n";
        
        stop.pb(fitAvg);
        if(gen>=199){
            smx=lmin;
            smn=lmax;
            for(int i=gen-199; i<=gen; i++){
                smx = max(smx, stop[i]);
                smn = min(smn, stop[i]);
            }
            if(smx-smn<=0.015) break;
        }

        sort(all(v));

        //CROSS-OVER
        for(int k=0; k<(8.0*v.size())/10.0; k+=2){
			int i=v[k].ss, j=v[k+1].ss;
			int x = rand()%courses;
            int y = rand()%(courses-x) + x;
            for(int l=x; l<=y; l++){
                swap(p[i][l].ss, p[j][l].ss);
            }
        }

        //MUTATION
        fori(i,v.size()-1){
            int z = rand()%1000 + 1;
            if(z<=5){
                int x = rand()%courses;
                p[v[i].ss][x].ss = 1 - p[v[i].ss][x].ss;
            }
        }

        gen++;
    }
    return 0;
}
