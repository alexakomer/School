# Generated by Django 3.1 on 2022-04-18 18:53

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('webapp', '0002_auto_20220418_1838'),
    ]

    operations = [
        migrations.AddField(
            model_name='user',
            name='services',
            field=models.CharField(default='netlifx', max_length=100),
            preserve_default=False,
        ),
        migrations.AlterField(
            model_name='user',
            name='username',
            field=models.CharField(max_length=20, primary_key=True, serialize=False, unique=True),
        ),
    ]