# Rendered Notebooks

{% for fil in site.static_files | where: "fil.extname", ".html" %}
## [{{ fil.name }}]({{ fil.path }})
Last updated: {{ fil.modified_time}}
{% endfor %}
