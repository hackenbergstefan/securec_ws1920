# Rendered Notebooks

{% assign static_htmls = site.static_files | where: "extname", ".html" %}

{% for fil in static_htmls %}
## [{{ fil.name }}]({{ fil.path }})
Last updated: {{ fil.modified_time}}
{% endfor %}
