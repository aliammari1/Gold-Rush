#include"header.h"
void initPerso(Personne *p)
{
	int i,j;
	char nom_image[20];
	for(i=0;i<6;i++)
	for(j=0;j<12;j++)
	{
	sprintf(nom_image,"images/%d/%d.png",i,j);
	p->img[i][j]=IMG_Load(nom_image);
	}
	p->pos.x=0;
	p->pos.y=400;
	p->pos_relative.x=-20;
	p->pos_relative.y=0;
	p->direction=0;
	p->frame=0;
	p->d=0;
	p->vX=5;
	p->up=0;
}
void afficherPerso(Personne p,SDL_Surface *screen)
{
	SDL_BlitSurface(p.img[p.direction][p.frame],NULL,screen,&p.pos);
}
void deplacerPerso(Personne *p,Uint32 dt)
{
if(p->direction==1)
p->pos.x+=0.5*(p->vX)*dt*dt+VIT*dt;
printf("%d\n",dt);
if(p->direction==3)
p->pos.x-=0.5*(p->vX)*dt*dt+VIT*dt;
if(p->vX>=MAX_VIT)
p->vX=MAX_VIT;
}
void animerPerso(Personne *p)
{
p->frame++;
if((p->pos_relative.x<=0)&&(p->pos_relative.x!=-20))
p->frame=2;
if(p->pos_relative.x>0)
p->frame=6;
if(p->frame>=11)
p->frame=0;
}
void saut(Personne *p)
{
p->pos_relative.y = (-0.0375)*(p->pos_relative.x)*(p->pos_relative.x)+15;
printf("pos_rely%d\n",p->pos_relative.y);
(p->pos_relative.x)++;
printf("pos_relx%d\n",p->pos_relative.x);
if(p->d==1)
p->pos.x-=10;
if(p->d==0)
p->pos.x+=10;
printf("pos_x%d\n",p->pos.x);
if(p->pos_relative.x<=0)
p->pos.y-=p->pos_relative.y;
else
p->pos.y+=p->pos_relative.y;
printf("pos_y%d\n",p->pos.y);
printf("\n");
}
